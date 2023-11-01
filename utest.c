#include "utest.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

const char* utest_result_names[] = {
    "OK",
    "ERROR",
    "SKIP"
};

typedef struct utest_result_data {
    utest_result_t res;
    struct timespec time;
} utest_result_data_t;

int utest_suite_main(const utest_suite_t* suite, void* data, int argc, const char* argv[]) {
    utest_test_t const* ptr = suite->tests;
    size_t n = 0;
    int max_name = 0, max_name_iter;
    while (ptr->name != NULL) {
        if ((max_name_iter = strlen(ptr->name)) > max_name)
            max_name = max_name_iter;
        ptr++;
        n++;
    }
    ptr = suite->tests;
    utest_result_data_t results[n];
    struct timespec stop, start;
    printf("running %s test suite...\n", suite->name);
    for (size_t i = 0; i < n; i++) {
        printf("running %s/%s test...\n", suite->name, ptr->name);
        clock_gettime(NULL, &start);
        results[i].res = ptr->test(data);
        clock_gettime(NULL, &stop);
        results[i].time.tv_sec = stop.tv_sec - start.tv_sec;
        results[i].time.tv_nsec = stop.tv_nsec - start.tv_nsec;
        ptr++;
    }

    printf("\n----- %s Test Suite ----- \n", suite->name);
    size_t count_success = 0, count_skip = 0;
    for (size_t i = 0; i < n; i++) {
        printf("%s/%-*s \t\t %-5s \t %lds %ldns\n",
                suite->name,
                max_name,
                suite->tests[i].name, 
                utest_result_names[results[i].res],
                results[i].time.tv_sec,
                results[i].time.tv_nsec);
        if (results[i].res == UTEST_OK)
            count_success++;
        else if (results[i].res == UTEST_SKIP)
            count_skip++;
    }
    double perc_success = 100 * (1.0 * count_success) / (1.0 * n),
        perc_skip = 100 * (1.0 * count_skip) / (1.0 * n);
    printf("%lu of %lu (%.0f%%) tests successful, %lu (%.0f%%) tests skipped.\n",
            count_success, n, perc_success, count_skip, perc_skip);
    return 0;
}

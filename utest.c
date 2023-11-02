#include "utest.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <argp.h>

static const char* utest_result_names[] = {
    "OK",
    "ERROR",
    "SKIP"
};

typedef struct utest_result_data {
    utest_result_t res;
    struct timespec time;
} utest_result_data_t;

const char* argp_program_version = "utest 0.1";
static char doc[] = "Unit testing suite using utest";
static char args_doc[] = "[TEST]";

static struct argp_option options[] = {
    { "param", 'p', "key=value", 0, "Set a parameter" },
    { "list", 'l', 0, 0, "List all tets" },
    { 0 }
};

struct arguments {
    char* args[1];
    int list;
};

static error_t parse_opt(int key, char* arg, struct argp_state* state) {
    struct arguments* args = state->input;
    switch (key) {
        case 'p':
            break;
        case 'l':
            args->list = 1;
            break;
        case ARGP_KEY_ARG:
            if (state->arg_num >= 1)
                argp_usage(state);
            args->args[state->arg_num] = arg;
            break;
        case ARGP_KEY_END:
            if (state->arg_num < 0)
                argp_usage(state);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int utest_suite_main(const utest_suite_t* suite, void* data, int argc, char* argv[]) {
    struct arguments args;
    argp_parse(&argp, argc, argv, 0, 0, &args);

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

    if (args.list) {
        printf("listing %lu tests...\n", n);
        for (size_t i = 0; i < n; i++) {
            printf("%s/%s\n", suite->name, suite->tests[i].name);
        }
    } else {
        utest_result_data_t results[n];
        struct timespec stop, start;
        printf("running %s test suite...\n", suite->name);
        for (size_t i = 0; i < n; i++) {
            printf("running %s/%s test...\n", suite->name, ptr->name);
            clock_gettime(CLOCK_REALTIME, &start);
            results[i].res = ptr->test(data);
            clock_gettime(CLOCK_REALTIME, &stop);
            results[i].time.tv_sec = stop.tv_sec - start.tv_sec;
            results[i].time.tv_nsec = stop.tv_nsec - start.tv_nsec;
            ptr++;
        }

        printf("\n----- %s Test Suite ----- \n", suite->name);
        size_t count_success = 0, count_skip = 0;
        for (size_t i = 0; i < n; i++) {
            printf("%s/%-*s \t\t %-5s \t %ld.%03lds\n",
                    suite->name,
                    max_name,
                    suite->tests[i].name, 
                    utest_result_names[results[i].res],
                    results[i].time.tv_sec,
                    results[i].time.tv_nsec / 1000);
            if (results[i].res == UTEST_OK)
                count_success++;
            else if (results[i].res == UTEST_SKIP)
                count_skip++;
        }
        double perc_success = 100 * (1.0 * count_success) / (1.0 * n),
            perc_skip = 100 * (1.0 * count_skip) / (1.0 * n);
        printf("%lu of %lu (%.0f%%) tests successful, %lu (%.0f%%) tests skipped.\n",
            count_success, n, perc_success, count_skip, perc_skip);

    }
    return 0;
}

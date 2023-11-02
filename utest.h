#ifndef __DMC_UTEST_H__
#define __DMC_UTEST_H__

typedef enum {
    UTEST_OK = 0,
    UTEST_ERR = 1,
    UTEST_SKIP = 2
} utest_result_t;

typedef utest_result_t (utest_testfn_t)(void*);

typedef struct utest_test {
    const char* name;
    utest_testfn_t* test;
} utest_test_t;

typedef struct utest_suite {
    const char* name;
    const utest_test_t* tests;
} utest_suite_t;

int utest_suite_main(const utest_suite_t* suite, void* data, int argc, char* argv[]);

#endif // __DMC_UTEST_H__

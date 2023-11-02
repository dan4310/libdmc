#include "../utest.h"

utest_result_t test_str(void* _) {
    return UTEST_OK;
}

utest_result_t test_log(void* _) {
    return UTEST_ERR;
}

utest_result_t test_vec(void* _) {
    return UTEST_OK;
}

utest_result_t test_something(void* _) {
    return UTEST_SKIP;
}

const utest_test_t my_tests[] = {
    { "str", test_str },
    { "log", test_log },
    { "vec", test_vec },
    { "something", test_something },
    { 0 }
};

const utest_suite_t my_suite = {
    "libdmc",
    my_tests
};

int main(int argc, char* argv[]) {
    return utest_suite_main(&my_suite, 0, argc, argv);
}

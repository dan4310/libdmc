#include "../log.h"
#include "../utest.h"

utest_result_t log_test_std(void* _) {
    log_error("Hello, Error!");
    log_warn("Hello, Warn!");
    log_info("Hello, Info!");
    log_debug("Hello, Debug!");
    return UTEST_OK;
}

utest_result_t log_test_fd(void* _) {
    FILE* fp = tmpfile();
    if (fp == NULL)
        return UTEST_ERR;
    flog_error(fp, "Hello, Error!");
    flog_warn(fp, "Hello, Warn!");
    flog_info(fp, "Hello, Info!");
    flog_debug(fp, "Hello, Debug!");

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char buff[size + 1];
    if (fread(buff, sizeof(char), size, fp) <= 0) {
        fclose(fp);
        return UTEST_ERR;
    }
    buff[size] = '\0';
    printf("From file:\n%s", buff);

    fclose(fp);
    return UTEST_OK;
}

const utest_test_t log_tests[] = {
    { "std", log_test_std },
    { "fd", log_test_fd },
    { 0 }
};

const utest_suite_t log_test_suite = {
    "log",
    log_tests
};

int main(int argc, char* argv[]) {
    return utest_suite_main(&log_test_suite, 0, argc, argv);
}

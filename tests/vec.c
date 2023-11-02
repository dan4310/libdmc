#include "../vec.h"
#include "../utest.h"
#include <stdio.h>
#include <time.h>

utest_result_t vec_test_push(void* _) {
    size_t n = 10;
    vec_int_t v;
    vec_init(&v);
    for (size_t i = 0; i < n; i++) {
        vec_push(&v, i);
    }
    if (v.len != n)
        return UTEST_ERR;

    for (size_t i  = 0; i < v.len; i++) {
        if (v.data[i] != i) {
            vec_free(&v);
            return UTEST_ERR;
        }
    }

    vec_free(&v);
    return UTEST_OK;
}

utest_result_t vec_test_remove(void* _) {
    size_t n = 10;
    vec_int_t v;
    vec_init(&v);
    for (size_t i = 0; i < n; i++) {
        vec_push(&v, i);
    }
    if (v.len != n) {
        vec_free(&v);
        return UTEST_ERR;
    }

    for (size_t i  = 0; i < n; i++)
        vec_remove(&v, i);

    if (v.len != 0) {
        vec_free(&v);
        return UTEST_ERR;
    }

    vec_free(&v);
    return UTEST_OK;
}

utest_result_t vec_test_insert(void* _) {
    size_t n = 10;
    vec_int_t v;
    vec_init(&v);
    for (int i = 0; i < n; i++) {
        vec_push(&v, i);
    }

    vec_insert(&v, 7, 5);
    if (vec_get(&v, 7) != 5) {
        vec_free(&v);
        return UTEST_ERR;
    }

    vec_insert(&v, 9, 100);
    if (vec_get(&v, 9) != 100) {
        vec_free(&v);
        return UTEST_ERR;
    }
    vec_free(&v);
    return UTEST_OK;
}

utest_result_t vec_test_cat(void* _) {
    size_t n = 10;
    vec_int_t a;
    int c_arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    const vec_int_t b = vec_lit(c_arr);
    vec_init(&a);
    for (int i = 0; i < n; i++) {
        vec_push(&a, i);
    }

    vec_cat(&a, &b);
    if (vec_len(&a) != n * 2) {
        return UTEST_ERR;
        vec_free(&a);
    }

    for (size_t i = 0; i < n; i++) {
        if (vec_get(&b, i) != vec_get(&a, i + n)) {
            vec_free(&a);
            return UTEST_ERR;
        }
    }

    vec_free(&a);
    return UTEST_OK;
}

const utest_test_t vec_tests[] = {
    { "push", vec_test_push },
    { "remove", vec_test_remove },
    { "insert", vec_test_insert },
    { "cat", vec_test_cat },
    { 0 }
};

const utest_suite_t vec_test_suite = {
    "vec",
    vec_tests
};


int main(int argc, char* argv[]) {
    return utest_suite_main(&vec_test_suite, 0, argc, argv);
}

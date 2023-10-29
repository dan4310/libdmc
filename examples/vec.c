#include "../vec.h"
#include <stdio.h>

int main(void) {
    vec_int_t v;
    vec_init(&v);
    for (size_t i = 0; i < 100; i++) {
        vec_add(&v, i);
    }
    vec_remove(&v, 97);
    for (size_t i = 0; i < v.len; i++) {
        printf("%d\n", v.data[i]);
    }
    int i = 0;
    vec_find(&v, 55, i);
    printf("found: %d\n", i);
    vec_find(&v, 97, i);
    printf("found: %d\n", i);
    vec_free(&v);
    return 0;
}

#include "../vec.h"
#include <stdio.h>
#include <time.h>

void vec_int_print(vec_int_t* v) {
    printf("[ ");
    for (size_t i = 0; i < v->len; i++) {
        if (i < v->len - 1)
            printf("%d, ", v->data[i]);
        else
         printf("%d ", v->data[i]);
    }
    printf("]\n");
}

int main(void) {
    srand(time(NULL));
    vec_int_t v;
    vec_init(&v);
    for (size_t i = 0; i < 10; i++) {
        vec_add(&v, rand());
    }
    vec_int_print(&v);
    printf("\n");

    int i = 0;
    vec_find(&v, v.data[3], i);
    printf("found %d: %d\n", v.data[10], i);
    vec_find(&v, 97, i);
    printf("found %d: %d\n", 97, i);
    vec_insert(&v, 4, 9999);
    vec_int_print(&v);

    vec_sort(&v, vec_int_cmp);
    printf("sorted: ");
    vec_int_print(&v);

    vec_add(&v, 25);
    vec_int_print(&v);
    vec_free(&v);

    return 0;
}

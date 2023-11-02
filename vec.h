#ifndef __DMC_VEC_H__
#define __DMC_VEC_H__

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define vec_t(T) struct { T* data; size_t len, cap; }

#define vec_unpack(V) (char**)&(V)->data, &(V)->len, &(V)->cap, sizeof(*(V)->data)

#define vec_lit(A) { A, sizeof(A)/sizeof(A[0]), 0 }

#define vec_init(V) memset((V), 0, sizeof(*(V)))
#define vec_free(V) free((V)->data)

int vec_expand(char** data, size_t* len, size_t* cap, size_t size, size_t n);
int _vec_cat(char** dest_data, size_t* dest_len, size_t* dest_cap, size_t dest_size,
               char** src_data, size_t* src_len, size_t* src_cap, size_t src_size);

#define vec_get(V, I) (V)->data[I]
#define vec_len(V) (V)->len

#define vec_push(V, X) vec_expand(vec_unpack(V), 1); (V)->data[(V)->len++] = X
#define vec_cat(V, X) _vec_cat(vec_unpack(V), vec_unpack(V))

#define vec_find(V, X, I)\
  do {\
    for ((I) = 0; (I) < (V)->len; (I)++) {\
      if ((V)->data[(I)] == (X)) break;\
    }\
    if ((I) == (V)->len) (I) = -1;\
  } while (0)

#define vec_remove(V, X)\
  do {\
    size_t idx__;\
    vec_find(V, X, idx__);\
    if (idx__ != -1) vec_splice(V, idx__, 1);\
  } while (0)

#define vec_splice(V, start, count)\
  ( _vec_splice(vec_unpack(V), start, count),\
    (V)->len -= (count) )

#define vec_insert(V, I, X)\
    (_vec_insert(vec_unpack(V), I) ? -1 : ((V)->data[I] = (X), 0), (V)->len++)

#define vec_sort(V, Fn)\
  qsort((V)->data, (V)->len, sizeof(*(V)->data), Fn)

#define vec_foreach(V, i) for (i = 0; i < (V)->len; i++)

void _vec_splice(char **data, size_t *length, size_t *capacity, size_t memsz, size_t start, size_t count);
int _vec_insert(char **data, size_t *length, size_t *capacity, size_t memsz, size_t idx);

typedef vec_t(int) vec_int_t;
typedef vec_t(char) vec_char_t;
typedef vec_t(void*) vec_void_t;
typedef vec_t(char*) vec_str_t;
typedef vec_t(long) vec_long_t;

static inline
int vec_int_cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

static inline
int vec_long_cmp(const void* a, const void* b) {
    return *(long*)a - *(long*)b;
}

static inline
int vec_char_cmp(const void* a, const void* b) {
    return *(char*)a - *(char*)b;
}

static inline
int vec_str_cmp(const void* a, const void* b) {
    return strcmp((char*)a, (char*)b);
}

#endif // __DMC_VEC_H__

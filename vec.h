#ifndef __DMC_VEC_H__
#define __DMC_VEC_H__

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define vec_t(T) struct { T* data; size_t len, cap; }

#define vec_unpack(V) (char**)&(V)->data, &(V)->len, &(V)->cap, sizeof(*(V)->data)

#define vec_init(V) memset((V), 0, sizeof(*(V)))
#define vec_free(V) free((V)->data)

int vec_expand(char** data, size_t* len, size_t* cap, size_t size);

#define vec_add(V, X) vec_expand(vec_unpack(V)); (V)->data[(V)->len++] = X
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

void _vec_splice(char **data, size_t *length, size_t *capacity, size_t memsz, size_t start, size_t count);

typedef vec_t(int) vec_int_t;
typedef vec_t(char) vec_char_t;
typedef vec_t(void*) vec_void_t;
typedef vec_t(char*) vec_str_t;
typedef vec_t(long) vec_long_t;

#endif // __DMC_VEC_H__

#include "vec.h"

int _vec_cat(char** dest_data, size_t* dest_len, size_t* dest_cap, size_t dest_size,
               char** src_data, size_t* src_len, size_t* src_cap, size_t src_size) {
    if (src_size != dest_size)
        return 1;
    int e = vec_expand(dest_data, dest_len, dest_cap, dest_size, *src_len);
    if (e != 0)
        return e;
    memcpy((*dest_data) + (*dest_len * dest_size), *src_data, (*src_len * src_size));
    *dest_len += *src_len;
    return 0;
}

int vec_expand(char** data, size_t* len, size_t* cap, size_t size, size_t n) {
    if (*len + n > *cap) {
      void *ptr;
      int cap_new = (*cap == 0) ? 1 : (*cap + n) << 1;
      ptr = realloc(*data, cap_new * size);
      if (ptr == NULL) return -1;
      *data = ptr;
      *cap = cap_new;
    }
    return 0;
}

void _vec_splice(char **data, size_t *length, size_t *capacity, size_t memsz, size_t start, size_t count) {
  (void) capacity;
  memmove(*data + start * memsz,
          *data + (start + count) * memsz,
          (*length - start - count) * memsz);
}

int _vec_insert(char **data, size_t *length, size_t *capacity, size_t memsz, size_t idx) {
  int err = vec_expand(data, length, capacity, memsz, 1);
  if (err) return err;
  memmove(*data + (idx + 1) * memsz,
          *data + idx * memsz,
          (*length - idx) * memsz);
  return 0;
}

#include "vec.h"

int vec_expand(char** data, size_t* len, size_t* cap, size_t size) {
    if (*len + 1 > *cap) {
      void *ptr;
      int n = (*cap == 0) ? 1 : *cap << 1;
      ptr = realloc(*data, n * size);
      if (ptr == NULL) return -1;
      *data = ptr;
      *cap = n;
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
  int err = vec_expand(data, length, capacity, memsz);
  if (err) return err;
  memmove(*data + (idx + 1) * memsz,
          *data + idx * memsz,
          (*length - idx) * memsz);
  return 0;
}

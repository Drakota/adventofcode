#ifndef ITER_H
#define ITER_H

#include "vec.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct iter {
  vec_t *vec;
  int index;
  void *value;
  bool loop;
} iter_t;

iter_t iter_begin_vec(vec_t *vec, bool loop);
void iter_next_vec(iter_t *it);

iter_t window_begin_vec(vec_t *vec, int size);
void window_next_vec(iter_t *it, int step);
void window_end_vec(iter_t *it);
#endif
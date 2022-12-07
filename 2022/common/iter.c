#include "iter.h"

vec_t *create_window_vec(vec_t *source, int offset, int size) {
  vec_t *window = malloc(sizeof(vec_t));
  init_vec(window);
  for (int i = offset; i < offset + size; i++) {
    push_vec(window, (void *)((size_t *)source->data)[i]);
  }
  return window;
}

iter_t iter_begin_vec(vec_t *vec) {
  iter_t iter;
  iter.vec = vec;
  iter.index = 0;
  if (iter.vec->size == 0) {
    iter.value = NULL;
  } else {
    iter.value = (void *)((size_t *)iter.vec->data)[iter.index];
  }
  return iter;
}

void iter_next_vec(iter_t *it) {
  if (it->value == NULL) {
    return;
  }
  if (it->index < it->vec->size - 1) {
    it->value = (void *)((size_t *)it->vec->data)[++it->index];
    return;
  }
  it->value = NULL;
}

iter_t window_begin_vec(vec_t *vec, int size) {
  iter_t iter;
  iter.vec = vec;
  iter.index = 0;
  iter.value = create_window_vec(iter.vec, iter.index, size);
  return iter;
}

void window_next_vec(iter_t *it, int step) {
  if (step < 1) {
    step = 1;
  }
  if (it->value == NULL) {
    return;
  }
  int window_size = ((vec_t *)(it->value))->size;
  free_vec(it->value);
  free(it->value);
  if (it->index < it->vec->size - window_size) {
    it->index += step;
    it->value = create_window_vec(it->vec, it->index, window_size);
    return;
  }
  it->value = NULL;
}

void window_end_vec(iter_t *it) {
  if (it->value == NULL) {
    return;
  }
  free_vec(it->value);
  free(it->value);
  it->value = NULL;
}
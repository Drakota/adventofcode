#include "vec.h"

void init_vec(vec_t *vec) {
  vec->size = 0;
  vec->capacity = 8;
  vec->data = malloc(vec->capacity * sizeof(void *));
}

void *get_vec(vec_t *vec, int index) {
  if (index >= vec->size) {
    return NULL;
  }
  return (void *)((size_t *)vec->data)[index];
}

void *delete_vec(vec_t *vec, int index) {
  if (index >= vec->size) {
    return NULL;
  }
  void *data = (void *)((size_t *)vec->data)[index];
  for (int i = index; i < vec->size - 1; i++) {
    ((size_t *)vec->data)[i] = ((size_t *)vec->data)[i + 1];
  }
  vec->size--;
  return data;
}

void push_vec(vec_t *vec, void *data) {
  if (vec->size == vec->capacity) {
    vec->capacity *= 2;
    vec->data = realloc(vec->data, vec->capacity * sizeof(void *));
  }
  ((size_t *)vec->data)[vec->size++] = (size_t)data;
}

void *pop_vec(vec_t *vec) {
  if (vec->size == 0) {
    return NULL;
  }
  return (void *)((size_t *)vec->data)[--vec->size];
}

void *pop_front_vec(vec_t *vec) { return delete_vec(vec, 0); }

void fill_vec_delim(vec_t *vec, char *str, char *delim,
                    void *(*map)(vec_t *vec, char *token)) {
  char *token = strtok(str, delim);
  while (token != NULL) {
    if (map != NULL) {
      push_vec(vec, map(vec, token));
    } else {
      push_vec(vec, token);
    }
    token = strtok(NULL, delim);
  }
}

void print_vec(vec_t *vec) {
  printf("[");
  for (int i = 0; i < vec->size; i++) {
    printf("%zu", ((size_t *)vec->data)[i]);
    if (i != vec->size - 1) {
      printf(", ");
    }
  }
  printf("]\n");
}

size_t sum_vec(vec_t *vec) {
  size_t sum = 0;
  for (int i = 0; i < vec->size; i++) {
    sum += ((size_t *)vec->data)[i];
  }
  return sum;
}

void free_vec(vec_t *vec) {
  free(vec->data);
  vec->data = NULL;
  vec->size = 0;
  vec->capacity = 0;
}
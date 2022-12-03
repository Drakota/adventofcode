#include "vec.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

char *strtokm(char *input, char *delimiter, char **saveptr) {
  char *string;
  if (input != NULL)
    string = input;
  else
    string = *saveptr;

  if (string == NULL)
    return string;

  char *end = strstr(string, delimiter);
  if (end == NULL) {
    char *tok = string;
    *saveptr = NULL;
    return tok;
  }

  char *tok = string;

  *end = '\0';
  *saveptr = end + strlen(delimiter);
  return tok;
}

void init_vec(vec_t *vec) {
  vec->size = 0;
  vec->capacity = 8;
  vec->data = malloc(vec->capacity * sizeof(void *));
}

void *get_vec(vec_t *vec, int index) {
  if (index >= vec->size || index < 0) {
    return NULL;
  }
  return (void *)((size_t *)vec->data)[index];
}

int find_vec(vec_t *vec, void *data) {
  for (int i = 0; i < vec->size; i++) {
    if (get_vec(vec, i) == data) {
      return i;
    }
  }
  return -1;
}

void *delete_vec(vec_t *vec, int index) {
  if (index >= vec->size || index < 0) {
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
  char *saveptr;
  char *token = strtokm(str, delim, &saveptr);
  while (token != NULL) {
    if (map != NULL) {
      void *data = map(vec, token);
      push_vec(vec, data);
    } else {
      push_vec(vec, token);
    }
    token = strtokm(NULL, delim, &saveptr);
  }
}

void fill_vec_str(vec_t *vec, char *data) {
  for (int i = 0; i < (int)strlen(data); i++) {
    push_vec(vec, (void *)(size_t)data[i]);
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

void sort_vec(vec_t *vec, int (*cmp)(const void *, const void *)) {
  qsort(vec->data, vec->size, sizeof(void *), cmp);
}

void intersect_vec(vec_t *vec1, vec_t *vec2) {
  for (int i = 0; i < vec1->size; i++) {
    if (find_vec(vec2, get_vec(vec1, i)) == -1) {
      delete_vec(vec1, i);
      i--;
    }
  }
}

void free_vec(vec_t *vec) {
  free(vec->data);
  vec->data = NULL;
  vec->size = 0;
  vec->capacity = 0;
}
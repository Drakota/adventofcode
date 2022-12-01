#include "callbacks.h"

void *parse_int(vec_t *vec, char *token) { return (void *)(size_t)atoi(token); }

int sort_ascending(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

int sort_descending(const void *a, const void *b) {
  return (*(int *)b - *(int *)a);
}

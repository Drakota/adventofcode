#include "vec.h"

void init_vec(vec_t *vec) {
  vec->size = 0;
  vec->capacity = 8;
  vec->unique = false;
  vec->data = malloc(vec->capacity * sizeof(void *));
}

void init_set(vec_t *vec) {
  vec->size = 0;
  vec->capacity = 8;
  vec->unique = true;
  vec->data = malloc(vec->capacity * sizeof(void *));
}

void init_vec_with_capacity(vec_t *vec, int capacity) {
  vec->size = 0;
  vec->capacity = capacity;
  vec->data = malloc(vec->capacity * sizeof(void *));
}

void init_vec_2d(vec_t *vec, int size) {
  vec->size = 0;
  vec->capacity = size;
  vec->data = malloc(vec->capacity * sizeof(void *));
  for (int i = 0; i < vec->capacity; i++) {
    vec_t *v = malloc(sizeof(vec_t));
    init_vec(v);
    push_vec(vec, v);
  }
}

void *get_vec(vec_t *vec, int index) {
  if (index >= vec->size || index < 0) {
    return NULL;
  }
  return (void *)((size_t *)vec->data)[index];
}

void *get_vec_2d(vec_t *vec, int row, int col) {
  if (row >= vec->size || row < 0) {
    return NULL;
  }
  vec_t *v = get_vec(vec, row);
  if (col >= v->size || col < 0) {
    return NULL;
  }
  return get_vec(v, col);
}

void set_vec(vec_t *vec, int index, void *data) {
  if (index >= vec->size || index < 0) {
    return;
  }
  ((size_t *)vec->data)[index] = (size_t)data;
}

int index_vec(vec_t *vec, void *data) {
  for (int i = 0; i < vec->size; i++) {
    if (get_vec(vec, i) == data) {
      return i;
    }
  }
  return -1;
}

void *find_vec(vec_t *vec, int (*map)(const void *, const void *), void *cmp) {
  for (int i = 0; i < vec->size; i++) {
    void *data = get_vec(vec, i);
    if (map(data, cmp) == 1) {
      return data;
    }
  }
  return NULL;
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

void push_set(vec_t *vec, void *data, int (*cmp)(const void *, const void *)) {
  if (vec->size == vec->capacity) {
    vec->capacity *= 2;
    vec->data = realloc(vec->data, vec->capacity * sizeof(void *));
  }
  if (cmp == NULL) {
    if (index_vec(vec, data) == -1) {
      ((size_t *)vec->data)[vec->size++] = (size_t)data;
    }
  } else {
    if (find_vec(vec, cmp, data) == NULL) {
      ((size_t *)vec->data)[vec->size++] = (size_t)data;
    }
  }
}

void push_front_vec(vec_t *vec, void *data) {
  if (vec->size == vec->capacity) {
    vec->capacity *= 2;
    vec->data = realloc(vec->data, vec->capacity * sizeof(void *));
  }
  for (int i = vec->size; i > 0; i--) {
    ((size_t *)vec->data)[i] = ((size_t *)vec->data)[i - 1];
  }
  ((size_t *)vec->data)[0] = (size_t)data;
  vec->size++;
}

void *pop_vec(vec_t *vec) {
  if (vec->size == 0) {
    return NULL;
  }
  return (void *)((size_t *)vec->data)[--vec->size];
}

void *pop_front_vec(vec_t *vec) { return delete_vec(vec, 0); }

void fill_vec_delim(vec_t *vec, char *str, char *delim,
                    void *(*map)(vec_t *vec, int index, char *token)) {
  int index = 0;
  char *saveptr;
  char *token = strtokm(str, delim, &saveptr);
  while (token != NULL) {
    if (map != NULL) {
      push_vec(vec, map(vec, index, token));
    } else {
      push_vec(vec, token);
    }
    token = strtokm(NULL, delim, &saveptr);
    index++;
  }
}

void fill_vec_2d_delim(vec_t *vec, char *str, char *delim,
                       void *(*map)(vec_t *, int, char *)) {
  int index = 0;
  char *saveptr;
  char *token = strtokm(str, delim, &saveptr);
  while (token != NULL) {
    if (map != NULL) {
      map(vec, index, token);
    }
    token = strtokm(NULL, delim, &saveptr);
    index++;
  }
}

void fill_vec_str(vec_t *vec, char *data,
                  void *(*map)(vec_t *vec, int index, char c)) {
  for (int i = 0; i < (int)strlen(data); i++) {
    if (map != NULL) {
      push_vec(vec, map(vec, i, (char)data[i]));
    } else {
      push_vec(vec, (void *)(size_t)data[i]);
    }
  }
}

void copy_vec(vec_t *src, vec_t *dst) {
  for (int i = 0; i < src->size; i++) {
    push_vec(dst, get_vec(src, i));
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

void print_2d_vec(vec_t *vec) {
  printf("[");
  int col = vec->size;
  int row = ((vec_t *)get_vec(vec, 0))->size;
  for (int i = 0; i < col; i++) {
    for (int j = 0; j < row; j++) {
      printf("%zu", (size_t)get_vec_2d(vec, i, j));
      if (j != ((vec_t *)get_vec(vec, i))->size - 1) {
        printf(", ");
      }
    }
  }
  printf("]\n");
}

size_t sum_vec(vec_t *vec, size_t (*map)(void *data)) {
  size_t sum = 0;
  for (int i = 0; i < vec->size; i++) {
    if (map != NULL) {
      sum += map(get_vec(vec, i));
    } else {
      sum += (size_t)get_vec(vec, i);
    }
  }
  return sum;
}

void sort_vec(vec_t *vec, int (*cmp)(const void *, const void *)) {
  qsort(vec->data, vec->size, sizeof(void *), cmp);
}

void intersect_vec(vec_t *vec1, vec_t *vec2,
                   int (*cmp)(const void *, const void *)) {
  for (int i = 0; i < vec1->size; i++) {
    if (cmp == NULL) {
      if (index_vec(vec2, get_vec(vec1, i)) == -1) {
        delete_vec(vec1, i);
        i--;
      } else {
        if (find_vec(vec2, cmp, get_vec(vec1, i)) == NULL) {
          delete_vec(vec1, i);
          i--;
        }
      }
    }
  }
}

void free_vec(vec_t *vec) {
  free(vec->data);
  vec->data = NULL;
  vec->size = 0;
  vec->capacity = 0;
}

void free_vec_2d(vec_t *vec) {
  for (int i = 0; i < vec->size; i++) {
    free_vec(get_vec(vec, i));
    free(get_vec(vec, i));
  }
  free_vec(vec);
}

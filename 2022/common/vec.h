#ifndef VEC_H
#define VEC_H

#include "utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vec {
  void *data;
  int size;
  int capacity;
  bool unique;
} vec_t;

void init_vec(vec_t *vec);
void init_set(vec_t *vec);
void init_vec_with_capacity(vec_t *vec, int capacity);
void init_vec_2d(vec_t *vec, int size);
void *get_vec(vec_t *vec, int index);
void *get_vec_2d(vec_t *vec, int row, int col);
void set_vec(vec_t *vec, int index, void *data);
int index_vec(vec_t *vec, void *data);
void *find_vec(vec_t *vec, int (*map)(const void *, const void *), void *cmp);
void *delete_vec(vec_t *vec, int index);
void push_vec(vec_t *vec, void *data);
void push_set(vec_t *vec, void *data, int (*cmp)(const void *, const void *));
void push_front_vec(vec_t *vec, void *data);
void *pop_vec(vec_t *vec);
void *pop_front_vec(vec_t *vec);
void fill_vec_delim(vec_t *vec, char *str, char *delim,
                    void *(*map)(vec_t *vec, int index, char *token));
void fill_vec_2d_delim(vec_t *vec, char *str, char *delim,
                       void *(*map)(vec_t *vec, int index, char *token));
void fill_vec_str(vec_t *vec, char *data,
                  void *(*map)(vec_t *vec, int index, char c));
void copy_vec(vec_t *src, vec_t *dst);
void print_vec(vec_t *vec);
void print_2d_vec(vec_t *vec);
size_t sum_vec(vec_t *vec, size_t (*map)(void *data));
void sort_vec(vec_t *vec, int (*cmp)(const void *, const void *));
void intersect_vec(vec_t *vec1, vec_t *vec2,
                   int (*cmp)(const void *, const void *));
void union_vec(vec_t *vec1, vec_t *vec2);
void free_vec(vec_t *vec);
void free_vec_2d(vec_t *vec);
#endif
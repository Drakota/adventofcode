#ifndef VEC_H
#define VEC_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vec {
  void *data;
  int size;
  int capacity;
} vec_t;

void init_vec(vec_t *vec);
void *get_vec(vec_t *vec, int index);
int find_vec(vec_t *vec, void *data);
void *delete_vec(vec_t *vec, int index);
void push_vec(vec_t *vec, void *data);
void *pop_vec(vec_t *vec);
void *pop_front_vec(vec_t *vec);
void fill_vec_delim(vec_t *vec, char *str, char *delim,
                    void *(*map)(vec_t *vec, char *token));
void fill_vec_str(vec_t *vec, char *data);
void copy_vec(vec_t *src, vec_t *dst);
void print_vec(vec_t *vec);
size_t sum_vec(vec_t *vec, size_t (*map)(void *data));
void sort_vec(vec_t *vec, int (*cmp)(const void *, const void *));
void intersect_vec(vec_t *vec1, vec_t *vec2);
void union_vec(vec_t *vec1, vec_t *vec2);
void free_vec(vec_t *vec);
#endif
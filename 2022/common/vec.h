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
void *delete_vec(vec_t *vec, int index);
void push_vec(vec_t *vec, void *data);
void *pop_vec(vec_t *vec);
void *pop_front_vec(vec_t *vec);
void fill_vec_delim(vec_t *vec, char *str, char *delim,
                    void *(*map)(vec_t *vec, char *token));
void print_vec(vec_t *vec);
size_t sum_vec(vec_t *vec);
void free_vec(vec_t *vec);
#endif
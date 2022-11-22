#ifndef VEC_H
#define VEC_H
#endif

typedef struct vec {
  void *data;
  int size;
  int capacity;
} vec_t;

typedef struct iter {
  vec_t *vec;
  int index;
  void *value;
} iter_t;

void init_vec(vec_t *vec);
void *get_vec(vec_t *vec, int index);
void *delete_vec(vec_t *vec, int index);
void push_vec(vec_t *vec, void *data);
void *pop_vec(vec_t *vec);
void *pop_front_vec(vec_t *vec);
void fill_vec_delim(vec_t *vec, char *str, char *delim,
                    void *(*map)(vec_t *vec, char *token));
iter_t iter_begin_vec(vec_t *vec);
void iter_next_vec(iter_t *it);
void free_vec(vec_t *vec);
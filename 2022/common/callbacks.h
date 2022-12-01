#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "vec.h"

void *parse_int(vec_t *vec, char *token);
int sort_ascending(const void *a, const void *b);
int sort_descending(const void *a, const void *b);

#endif
#include "../common/aoc.h"
#include "../common/vec.h"
#include "input/data.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *map(vec_t *vec, char *token) { return (void *)(size_t)atoi(token); }

int part1(char *input) {
  vec_t v;
  init_vec(&v);
  fill_vec_delim(&v, input, "\n", map);

  size_t v1 = (size_t)pop_vec(&v);
  size_t v2 = (size_t)pop_vec(&v);
  size_t v3 = (size_t)pop_vec(&v);
  size_t v4 = (size_t)pop_vec(&v);
  size_t v5 = (size_t)pop_vec(&v);
  size_t v6 = (size_t)pop_vec(&v);
  size_t v7 = (size_t)pop_front_vec(&v);
  size_t v8 = (size_t)pop_front_vec(&v);
  size_t v9 = (size_t)pop_front_vec(&v);
  size_t v10 = (size_t)pop_front_vec(&v);

  for (iter_t it = iter_begin_vec(&v); it.value != NULL; iter_next_vec(&it)) {
    printf("%d, %lu\n", it.index, (size_t)it.value);
  }

  free_vec(&v);
  return 10;
}

int part2(char *input) {
  printf("Part 2: %s\n", input);
  return 20;
}

AOC_MAIN(d01, 10, 20)
#include "../common/aoc.h"
#include "../common/iter.h"
#include "../common/vec.h"
#include "input/data.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *parse_line(vec_t *vec, char *token) {
  return (void *)(size_t)atoi(token);
}

int part1(char *input) {
  vec_t v;
  init_vec(&v);
  fill_vec_delim(&v, input, "\n", parse_line);

  int increased = 0;
  iter_t it = iter_begin_vec(&v);
  size_t compare = (size_t)it.value;

  for (; it.value != NULL; iter_next_vec(&it)) {
    if ((size_t)it.value > compare) {
      increased++;
    }
    compare = (size_t)it.value;
  }

  free_vec(&v);
  return increased;
}

int part2(char *input) {
  vec_t v;
  init_vec(&v);
  fill_vec_delim(&v, input, "\n", parse_line);

  int increased = 0;
  iter_t it = window_begin_vec(&v, 3);
  size_t compare = sum_vec(it.value);

  for (; it.value != NULL; window_next_vec(&it)) {
    if (sum_vec((vec_t *)it.value) > compare) {
      increased++;
    }
    compare = sum_vec(it.value);
  }

  window_end_vec(&it);
  free_vec(&v);
  return increased;
}

AOC_MAIN(d01, 1466, 1491)
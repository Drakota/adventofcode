#include "../common/headers.h"
#include "input/data.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef union movement {
  struct {
    int8_t amount;
    int8_t src;
    int8_t dst;
  };
  void *data;
} movement_t;

void *parse_movements(vec_t *vec, int index, char *token) {
  int8_t amount, src, dst;
  sscanf(token, "move %hhd from %hhd to %hhd", &amount, &src, &dst);
  movement_t mov = {.amount = amount, .src = src, .dst = dst};
  return mov.data;
}

void parse_stacks(vec_t *vec, int index, char *token) {
  int stack = 0;
  for (int i = 1; i <= 33; i += 4) {
    if (token[i] != ' ') {
      push_vec((vec_t *)get_vec(vec, stack), (void *)(size_t)token[i]);
    }
    stack++;
  }
}

#define SOLUTION(part, func)                                                   \
  vec_t procedure, stacks, movements;                                          \
  init_vec(&procedure);                                                        \
  init_vec(&movements);                                                        \
  init_vec_2d(&stacks, 9);                                                     \
  fill_vec_delim(&procedure, input, "\n\n", NULL);                             \
  fill_vec_2d_delim(&stacks, get_vec(&procedure, 0), "\n", parse_stacks);      \
  fill_vec_delim(&movements, get_vec(&procedure, 1), "\n", parse_movements);   \
                                                                               \
  for (int i = 0; i < movements.size; i++) {                                   \
    movement_t mov = (movement_t)get_vec(&movements, i);                       \
    vec_t *src = get_vec(&stacks, mov.src - 1);                                \
    vec_t *dst = get_vec(&stacks, mov.dst - 1);                                \
    func                                                                       \
  }                                                                            \
                                                                               \
  char answer[10] = {0};                                                       \
  for (int i = 0; i < stacks.size; i++) {                                      \
    char top = (char)(size_t)get_vec_2d(&stacks, i, 0);                        \
    answer[i] = top;                                                           \
  }                                                                            \
  printf("Part " part ": %s\n", answer);                                       \
                                                                               \
  free_vec_2d(&stacks);                                                        \
  free_vec(&movements);                                                        \
  free_vec(&procedure);

int part1(char *input) {
  // clang-format off
  SOLUTION(
      "1",
      for (int j = 0; j < mov.amount; j++) { 
        push_front_vec(dst, pop_front_vec(src)); 
      }
  )
  // clang-format on
  return 0;
}

int part2(char *input) {
  // clang-format off
  SOLUTION(
      "2",
      for (int j = mov.amount - 1; j >= 0; j--) { 
        push_front_vec(dst, delete_vec(src, j));
      }
  )
  // clang-format on
  return 0;
}

AOC_MAIN(d05, 0, 0)
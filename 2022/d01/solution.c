#include "../common/headers.h"
#include "input/data.h"

typedef struct answer {
  int p1;
  int p2;
} answer_t;

void *parse_line(vec_t *vec, char *token) {
  vec_t total_calories;
  init_vec(&total_calories);
  fill_vec_delim(&total_calories, token, "\n", parse_int);
  size_t sum = sum_vec(&total_calories, NULL);
  free_vec(&total_calories);
  return (void *)sum;
}

answer_t solution(char *input) {
  vec_t elf_calories;
  init_vec(&elf_calories);
  fill_vec_delim(&elf_calories, input, "\n\n", parse_line);
  sort_vec(&elf_calories, sort_descending);

  size_t top_3_sum = 0;
  for (int i = 0; i < 3; i++) {
    top_3_sum += ((size_t *)elf_calories.data)[i];
  }
  size_t max = (size_t)get_vec(&elf_calories, 0);
  answer_t answer = {max, top_3_sum};

  free_vec(&elf_calories);
  return answer;
}

int part1(char *input) { return solution(input).p1; }
int part2(char *input) { return solution(input).p2; }

AOC_MAIN(d01, 70509, 208567)
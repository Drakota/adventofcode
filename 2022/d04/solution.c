#include "../common/headers.h"
#include "input/data.h"

typedef struct answer {
  int p1;
  int p2;
} answer_t;

void *split_sections(vec_t *vec, int index, char *token) {
  char *line = strtok(token, "-");
  int s1 = atoi(line);
  line = strtok(NULL, ",");
  int e1 = atoi(line);
  line = strtok(NULL, "-");
  int s2 = atoi(line);
  line = strtok(NULL, ",");
  int e2 = atoi(line);

  size_t p1 = (s1 <= s2 && e2 <= e1) || (s1 >= s2 && e2 >= e1);
  size_t p2 = (s1 < s2 && e1 < s2) || (s1 > s2 && s1 > e2);
  size_t result = (!p2 << 1) | p1;

  return (void *)result;
}

size_t full_overlaps(void *data) { return (size_t)data & 1; }
size_t partial_overlaps(void *data) { return (size_t)data >> 1; }

answer_t solution(char *input) {
  vec_t vec;
  init_vec(&vec);
  fill_vec_delim(&vec, input, "\n", split_sections);
  answer_t answer = {
      sum_vec(&vec, full_overlaps),
      sum_vec(&vec, partial_overlaps),
  };
  free_vec(&vec);
  return answer;
}

int part1(char *input) { return solution(input).p1; }
int part2(char *input) { return solution(input).p2; }

AOC_MAIN(d04, 513, 878)
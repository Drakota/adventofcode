#include "../common/headers.h"
#include "input/data.h"

int solution(char *input, int window_size) {
  vec_t buffer;
  init_vec(&buffer);
  fill_vec_str(&buffer, input, NULL);

  iter_t iter = window_begin_vec(&buffer, window_size);
  for (; iter.value != NULL; window_next_vec(&iter, 1)) {
    vec_t *marker = iter.value;
    for (int i = 0; i < marker->size; i++) {
      for (int j = i + 1; j < marker->size; j++) {
        if (get_vec(marker, i) == get_vec(marker, j)) {
          goto break_outer_loop;
        }
      }
    }
    break;
  break_outer_loop:;
  }

  int result = iter.index + window_size;
  window_end_vec(&iter);
  free_vec(&buffer);
  return result;
}

int part1(char *input) { return solution(input, 4); }

int part2(char *input) { return solution(input, 14); }

AOC_MAIN(d06, 1210, 3476)
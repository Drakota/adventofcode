#include "../common/headers.h"
#include "input/data.h"

size_t char_to_score(char c) {
  assert(islower(c) || isupper(c));
  return c >= 'a' ? (size_t)c - '`' : (size_t)c - '&';
}

void *split_into_compartments(vec_t *vec, char *token) {
  int compartment_size = strlen(token) / 2;
  vec_t compartment1, compartment2;
  init_vec(&compartment1);
  init_vec(&compartment2);

  for (int i = 0; i < compartment_size; i++) {
    push_vec(&compartment1, (void *)(size_t)token[i]);
    push_vec(&compartment2, (void *)(size_t)token[i + compartment_size]);
  }
  intersect_vec(&compartment1, &compartment2);
  size_t common_item_type = (size_t)get_vec(&compartment1, 0);

  free_vec(&compartment1);
  free_vec(&compartment2);
  return (void *)char_to_score(common_item_type);
}

int part1(char *input) {
  vec_t rucksacks;
  init_vec(&rucksacks);
  fill_vec_delim(&rucksacks, input, "\n", split_into_compartments);
  size_t sum = sum_vec(&rucksacks, NULL);
  free_vec(&rucksacks);
  return sum;
}

int part2(char *input) {
  vec_t rucksacks;
  init_vec(&rucksacks);
  fill_vec_delim(&rucksacks, input, "\n", NULL);

  size_t sum = 0;
  iter_t iter = window_begin_vec(&rucksacks, 3);
  for (; iter.value != NULL; window_next_vec(&iter, 3)) {
    vec_t compartment1, compartment2, compartment3;
    init_vec(&compartment1);
    init_vec(&compartment2);
    init_vec(&compartment3);

    fill_vec_str(&compartment1, get_vec(iter.value, 0));
    fill_vec_str(&compartment2, get_vec(iter.value, 1));
    fill_vec_str(&compartment3, get_vec(iter.value, 2));
    intersect_vec(&compartment1, &compartment2);
    intersect_vec(&compartment1, &compartment3);

    sum += char_to_score((size_t)get_vec(&compartment1, 0));
    free_vec(&compartment1);
    free_vec(&compartment2);
    free_vec(&compartment3);
  }

  window_end_vec(&iter);
  free_vec(&rucksacks);
  return sum;
}

AOC_MAIN(d03, 8493, 2552)
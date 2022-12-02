#include "../common/aoc.h"
#include "../common/callbacks.h"
#include "../common/iter.h"
#include "../common/vec.h"
#include "input/data.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void *parse_match_outcome(vec_t *vec, char *token) {
  char opponent_move = token[0] - '@';
  char encrypted_move = token[2] - 'W';
  size_t score = encrypted_move;

  if (opponent_move == encrypted_move) {
    return (void *)(score + 3);
  }

  opponent_move++;
  opponent_move %= 3;
  encrypted_move %= 3;

  return opponent_move == encrypted_move ? (void *)(score + 6) : (void *)score;
}

void *parse_score(vec_t *vec, char *token) {
  char opponent_move = token[0] - '@';
  char match_outcome = token[2] - 'W';
  size_t score = (match_outcome - 1) * 3;

  if (match_outcome == 1) {
    score += ((opponent_move + 1) % 3) + 1;
  } else if (match_outcome == 2) {
    score += opponent_move;
  } else {
    score += (opponent_move % 3) + 1;
  }

  return (void *)score;
}

int part1(char *input) {
  vec_t matches;
  init_vec(&matches);
  fill_vec_delim(&matches, input, "\n", parse_match_outcome);
  int total = sum_vec(&matches);
  free_vec(&matches);
  return total;
}

int part2(char *input) {
  vec_t matches;
  init_vec(&matches);
  fill_vec_delim(&matches, input, "\n", parse_score);
  int total = sum_vec(&matches);
  free_vec(&matches);
  return total;
}

AOC_MAIN(d02, 10941, 13071)
#include "../common/headers.h"
#include "input/data.h"

void *parse_heights(vec_t *vec, int index, char c) {
  return (void *)(size_t)(c - '0');
}

void *parse_rows(vec_t *vec, int index, char *token) {
  vec_t *row = malloc(sizeof(vec_t));
  init_vec(row);
  fill_vec_str(row, token, parse_heights);
  push_vec(vec, row);
  return NULL;
}

int part1(char *input) {
  vec_t grid;
  init_vec(&grid);
  fill_vec_2d_delim(&grid, input, "\n", parse_rows);
  vec_t *row = get_vec(&grid, 0);

  int trees_visible = 0;
  for (int i = 0; i < grid.size; i++) {
    for (int j = 0; j < row->size; j++) {
      bool up_vis = true, down_vis = true, left_vis = true, right_vis = true;

      for (int k = i - 1; k >= 0; k--) {
        if (get_vec_2d(&grid, k, j) >= get_vec_2d(&grid, i, j)) {
          up_vis = false;
          break;
        }
      }

      for (int k = i + 1; k < grid.size; k++) {
        if (get_vec_2d(&grid, k, j) >= get_vec_2d(&grid, i, j)) {
          down_vis = false;
          break;
        }
      }

      for (int k = j - 1; k >= 0; k--) {
        if (get_vec_2d(&grid, i, k) >= get_vec_2d(&grid, i, j)) {
          left_vis = false;
          break;
        }
      }

      for (int k = j + 1; k < row->size; k++) {
        if (get_vec_2d(&grid, i, k) >= get_vec_2d(&grid, i, j)) {
          right_vis = false;
          break;
        }
      }

      if (up_vis || down_vis || left_vis || right_vis) {
        trees_visible++;
      }
    }
  }

  free_vec_2d(&grid);
  return trees_visible;
}

int part2(char *input) {
  vec_t grid;
  init_vec(&grid);
  fill_vec_2d_delim(&grid, input, "\n", parse_rows);
  vec_t *row = get_vec(&grid, 0);

  int highest_scenic_score = 0;
  for (int i = 0; i < grid.size; i++) {
    for (int j = 0; j < row->size; j++) {
      int up_dist = 0, down_dist = 0, left_dist = 0, right_dist = 0;

      for (int k = i - 1; k >= 0; k--) {
        up_dist++;
        if (get_vec_2d(&grid, k, j) >= get_vec_2d(&grid, i, j)) {
          break;
        }
      }

      for (int k = i + 1; k < grid.size; k++) {
        down_dist++;
        if (get_vec_2d(&grid, k, j) >= get_vec_2d(&grid, i, j)) {
          break;
        }
      }

      for (int k = j - 1; k >= 0; k--) {
        left_dist++;
        if (get_vec_2d(&grid, i, k) >= get_vec_2d(&grid, i, j)) {
          break;
        }
      }

      for (int k = j + 1; k < row->size; k++) {
        right_dist++;
        if (get_vec_2d(&grid, i, k) >= get_vec_2d(&grid, i, j)) {
          break;
        }
      }

      int scenic_score = up_dist * down_dist * left_dist * right_dist;
      if (highest_scenic_score < scenic_score) {
        highest_scenic_score = scenic_score;
      }
    }
  }

  free_vec_2d(&grid);
  return highest_scenic_score;
}

AOC_MAIN(d08, 1832, 157320)
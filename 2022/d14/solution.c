#include "../common/headers.h"
#include "input/data.h"

#define SAND_SPAWN_X 500
#define SAND_SPAWN_Y 0
#define CAVE_SIZE 700
#define CAVE_EMPTY_VALUE 0
#define CAVE_SAND_VALUE 1
#define CAVE_WALL_VALUE 2

typedef struct problem {
  int (*cave)[CAVE_SIZE][CAVE_SIZE];
  int max_depth;
} problem_t;

void parse_cave(char *token, int index, void *data) {
  problem_t *problem = (problem_t *)data;
  int(*cave)[CAVE_SIZE][CAVE_SIZE] = problem->cave;
  int cursor = 0;
  int chars_read;

  int start_x;
  int start_y;
  sscanf(token, "%d,%d ->  %n", &start_x, &start_y, &chars_read);
  cursor += chars_read;

  int end_x;
  int end_y;
  while (sscanf(token + cursor, "%d,%d ->  %n", &end_x, &end_y, &chars_read) ==
         2) {
    cursor += chars_read;
    if (end_y > problem->max_depth) {
      problem->max_depth = end_y;
    }
    while ((start_x != end_x) || (start_y != end_y)) {
      (*cave)[start_x][start_y] = CAVE_WALL_VALUE;
      if (start_x < end_x) {
        start_x++;
      } else if (start_x > end_x) {
        start_x--;
      } else if (start_y < end_y) {
        start_y++;
      } else if (start_y > end_y) {
        start_y--;
      }
    }
    (*cave)[start_x][start_y] = CAVE_WALL_VALUE;
  }
}

int sand_simulation(int cave[CAVE_SIZE][CAVE_SIZE], int max_depth) {
  int sand_units = 0;
  while (true) {
    int sand_x = SAND_SPAWN_X;
    int sand_y = SAND_SPAWN_Y;

    while (true) {
      if (sand_y > max_depth) {
        break;
      }

      if (cave[sand_x][sand_y + 1] == CAVE_EMPTY_VALUE) {
        sand_y++;
      } else if (cave[sand_x - 1][sand_y + 1] == CAVE_EMPTY_VALUE) {
        sand_x--;
        sand_y++;
      } else if (cave[sand_x + 1][sand_y + 1] == CAVE_EMPTY_VALUE) {
        sand_x++;
        sand_y++;
      } else {
        cave[sand_x][sand_y] = CAVE_SAND_VALUE;
        break;
      }
    }

    if (((sand_x == SAND_SPAWN_X) && (sand_y == SAND_SPAWN_Y)) ||
        (sand_y > max_depth)) {
      break;
    }
    sand_units++;
  }
  return sand_units;
}

int part1(char *input) {
  int cave[CAVE_SIZE][CAVE_SIZE] = {0};
  problem_t problem = {.cave = &cave, .max_depth = 0};
  map_delim(input, "\n", parse_cave, &problem);
  return sand_simulation(cave, CAVE_SIZE);
}

int part2(char *input) {
  int cave[CAVE_SIZE][CAVE_SIZE] = {0};
  problem_t problem = {.cave = &cave, .max_depth = 0};
  map_delim(input, "\n", parse_cave, &problem);

  // Ground layer
  for (int x = 0; x < CAVE_SIZE; x++) {
    cave[x][problem.max_depth + 2] = CAVE_WALL_VALUE;
  }

  return sand_simulation(cave, problem.max_depth + 2) + 1;
}

AOC_MAIN(d14, 964, 32041)
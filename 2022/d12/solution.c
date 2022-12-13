#include "../common/headers.h"
#include "input/data.h"

typedef struct point {
  int x;
  int y;
  int dist;
  char c;
} point_t;

typedef struct problem {
  vec_t *grid;
  point_t start;
  point_t end;
  int part;
} problem_t;

void *parse_grid(vec_t *vec, int index, char *token) {
  vec_t *line = get_vec(vec, index);
  fill_vec_str(line, token, NULL);
  return NULL;
}

int path_find(problem_t *problem) {
  vec_t queue;
  init_vec(&queue);
  push_vec(&queue, &problem->start);

  int height = problem->grid->size;
  int width = ((vec_t *)get_vec(problem->grid, 0))->size;

  bool visited[height][width];
  memset(visited, false, sizeof(visited));
  visited[problem->start.y][problem->start.x] = true;

  int min = INT32_MAX;
  while (queue.size > 0) {
    point_t *point = pop_front_vec(&queue);

    bool is_end = problem->part == 1 ? (point->x == problem->end.x &&
                                        point->y == problem->end.y)
                                     : point->c == 'a';
    if (is_end) {
      if (point->dist < min) {
        min = point->dist;
      }
    }

    for (int i = 0; i < 4; i++) {
      int x = point->x;
      int y = point->y;

      switch (i) {
      case 0:
        x--;
        break;
      case 1:
        x++;
        break;
      case 2:
        y--;
        break;
      case 3:
        y++;
        break;
      }

      if (x < 0 || x >= width || y < 0 || y >= height) {
        continue;
      }

      char c = (char)(size_t)get_vec_2d(problem->grid, y, x);
      if (problem->part == 1 && c == 'E') {
        c = 'z' + 1;
      }

      bool valid_move =
          problem->part == 1 ? (c <= (point->c + 1)) : (point->c <= (c + 1));
      if (!visited[y][x] && valid_move) {
        visited[y][x] = true;
        point_t *new_point = malloc(sizeof(point_t));
        new_point->x = x;
        new_point->y = y;
        new_point->dist = point->dist + 1;
        memset(&new_point->c, c, sizeof(char));
        push_vec(&queue, new_point);
      }
    }

    if (point != &problem->start) {
      free(point);
    }
  }

  free_vec(&queue);
  return min;
}

int part1(char *input) {
  vec_t grid;
  init_vec_2d(&grid, 41);
  fill_vec_2d_delim(&grid, input, "\n", parse_grid);

  problem_t problem = {};
  problem.grid = &grid;

  for (int y = 0; y < grid.size; y++) {
    vec_t *line = get_vec(&grid, y);
    for (int x = 0; x < line->size; x++) {
      char c = (char)(size_t)get_vec_2d(&grid, y, x);
      if (c == 'S') {
        problem.start.x = x;
        problem.start.y = y;
        problem.start.dist = 0;
        problem.start.c = 'a';
      } else if (c == 'E') {
        problem.end.x = x;
        problem.end.y = y;
        problem.end.dist = 0;
        problem.end.c = 'a';
      }
    }
  }

  problem.part = 1;
  int dist = path_find(&problem);

  free_vec_2d(&grid);
  return dist;
}

int part2(char *input) {
  vec_t grid;
  init_vec_2d(&grid, 41);
  fill_vec_2d_delim(&grid, input, "\n", parse_grid);

  problem_t problem = {};
  problem.grid = &grid;

  for (int y = 0; y < grid.size; y++) {
    vec_t *line = get_vec(&grid, y);
    for (int x = 0; x < line->size; x++) {
      char c = (char)(size_t)get_vec_2d(&grid, y, x);
      if (c == 'E') {
        problem.start.x = x;
        problem.start.y = y;
        problem.start.dist = 0;
        problem.start.c = 'z';
      }
    }
  }

  problem.part = 2;
  int dist = path_find(&problem);

  free_vec_2d(&grid);
  return dist;
}

AOC_MAIN(d12, 456, 454)
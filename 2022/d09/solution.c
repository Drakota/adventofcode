#include "../common/headers.h"
#include "input/data.h"

typedef struct point {
  int16_t x;
  int16_t y;
} point_t;

typedef struct data {
  point_t *knots;
  vec_t *visited;
  int knot_count;
} data_t;

int sign(int dir) {
  if (dir > 0) {
    return 1;
  } else if (dir < 0) {
    return -1;
  } else {
    return 0;
  }
}

void parse_motions(char *token, int index, void *data) {
  data_t *d = data;
  char direction;
  int steps;
  sscanf(token, "%c %d", &direction, &steps);

  for (int _ = 0; _ < steps; _++) {
    if (direction == 'L') {
      d->knots[0].x -= 1;
    } else if (direction == 'R') {
      d->knots[0].x += 1;
    } else if (direction == 'U') {
      d->knots[0].y += 1;
    } else if (direction == 'D') {
      d->knots[0].y -= 1;
    }

    for (int k = 1; k < d->knot_count; k++) {
      if (abs(d->knots[k - 1].x - d->knots[k].x) >= 2 ||
          abs(d->knots[k - 1].y - d->knots[k].y) >= 2) {
        d->knots[k].x = sign(d->knots[k - 1].x - d->knots[k].x);
        d->knots[k].y = sign(d->knots[k - 1].y - d->knots[k].y);
      }
    }

    void *tail_location_packed =
        (void *)(size_t)((d->knots[d->knot_count - 1].y << 16) |
                         (d->knots[d->knot_count - 1].x & 0xFFFF));
    if (index_vec(d->visited, tail_location_packed) == -1) {
      push_vec(d->visited, tail_location_packed);
    }
  }
}

int part1(char *input) {
  data_t data = {};
  point_t knots[2] = {};
  data.knots = knots;
  vec_t visited;
  init_vec(&visited);
  data.visited = &visited;
  data.knot_count = 2;
  map_delim(input, "\n", parse_motions, &data);

  int unique_positions = data.visited->size;
  free_vec(data.visited);
  return unique_positions;
}

int part2(char *input) {
  data_t data = {};
  point_t knots[10] = {};
  data.knots = knots;
  vec_t visited;
  init_vec(&visited);
  data.visited = &visited;
  data.knot_count = 10;
  map_delim(input, "\n", parse_motions, &data);

  int unique_positions = data.visited->size;
  free_vec(data.visited);
  return unique_positions;
}

AOC_MAIN(d09, 6642, 2765)
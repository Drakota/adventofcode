#include "../common/headers.h"
#include "input/data.h"

typedef struct droplet {
  int x;
  int y;
  int z;
} droplet_t;

int cmp_droplets(const void *a, const void *b) {
  const droplet_t *droplet_a = a;
  const droplet_t *droplet_b = b;
  if (droplet_a->x == droplet_b->x && droplet_a->y == droplet_b->y &&
      droplet_a->z == droplet_b->z) {
    return 1;
  }
  return 0;
}

void *parse_droplets(vec_t *vec, int index, char *token) {
  droplet_t *droplet = malloc(sizeof(droplet_t));
  sscanf(token, "%d,%d,%d", &droplet->x, &droplet->y, &droplet->z);
  return droplet;
}

int min(int a, int b, int c) {
  int min = a;
  if (b < min) {
    min = b;
  }
  if (c < min) {
    min = c;
  }
  return min;
}

int max(int a, int b, int c) {
  int max = a;
  if (b > max) {
    max = b;
  }
  if (c > max) {
    max = c;
  }
  return max;
}

vec_t *neighbours(droplet_t *droplet, int min_axis, int max_axis) {
  vec_t *n = malloc(sizeof(vec_t));
  init_set(n);

  if (droplet->x > min_axis) {
    droplet_t *neighbour = malloc(sizeof(droplet_t));
    neighbour->x = droplet->x - 1;
    neighbour->y = droplet->y;
    neighbour->z = droplet->z;
    push_set(n, neighbour, cmp_droplets);
  }
  if (droplet->x < max_axis) {
    droplet_t *neighbour = malloc(sizeof(droplet_t));
    neighbour->x = droplet->x + 1;
    neighbour->y = droplet->y;
    neighbour->z = droplet->z;
    push_set(n, neighbour, cmp_droplets);
  }
  if (droplet->y > min_axis) {
    droplet_t *neighbour = malloc(sizeof(droplet_t));
    neighbour->x = droplet->x;
    neighbour->y = droplet->y - 1;
    neighbour->z = droplet->z;
    push_set(n, neighbour, cmp_droplets);
  }
  if (droplet->y < max_axis) {
    droplet_t *neighbour = malloc(sizeof(droplet_t));
    neighbour->x = droplet->x;
    neighbour->y = droplet->y + 1;
    neighbour->z = droplet->z;
    push_set(n, neighbour, cmp_droplets);
  }
  if (droplet->z > min_axis) {
    droplet_t *neighbour = malloc(sizeof(droplet_t));
    neighbour->x = droplet->x;
    neighbour->y = droplet->y;
    neighbour->z = droplet->z - 1;
    push_set(n, neighbour, cmp_droplets);
  }
  if (droplet->z < max_axis) {
    droplet_t *neighbour = malloc(sizeof(droplet_t));
    neighbour->x = droplet->x;
    neighbour->y = droplet->y;
    neighbour->z = droplet->z + 1;
    push_set(n, neighbour, cmp_droplets);
  }

  return n;
}

int part1(char *input) {
  vec_t droplets;
  init_vec(&droplets);
  fill_vec_delim(&droplets, input, "\n", parse_droplets);

  int min_axis = INT_MAX;
  int max_axis = INT_MIN;
  for (int i = 0; i < droplets.size; i++) {
    droplet_t *droplet = get_vec(&droplets, i);
    int min_point = min(droplet->x, droplet->y, droplet->z);
    int max_point = max(droplet->x, droplet->y, droplet->z);
    if (min_point < min_axis) {
      min_axis = min_point;
    }
    if (max_point > max_axis) {
      max_axis = max_point;
    }
  }
  min_axis -= 1;
  max_axis += 1;

  int droplet_area = droplets.size * 6;
  for (int i = 0; i < droplets.size; i++) {
    droplet_t *droplet = get_vec(&droplets, i);
    vec_t *n = neighbours(droplet, min_axis, max_axis);
    intersect_vec(n, &droplets, cmp_droplets);

    droplet_area -= n->size;

    for (int j = 0; j < n->size; j++) {
      free(get_vec(n, j));
    }
    free_vec(n);
  }

  for (int i = 0; i < droplets.size; i++) {
    free(get_vec(&droplets, i));
  }
  free_vec(&droplets);
  return droplet_area;
}

int part2(char *input) {
  vec_t droplets;
  init_vec(&droplets);
  fill_vec_delim(&droplets, input, "\n", parse_droplets);

  int min_axis = INT_MAX;
  int max_axis = INT_MIN;
  for (int i = 0; i < droplets.size; i++) {
    droplet_t *droplet = get_vec(&droplets, i);
    int min_point = min(droplet->x, droplet->y, droplet->z);
    int max_point = max(droplet->x, droplet->y, droplet->z);
    if (min_point < min_axis) {
      min_axis = min_point;
    }
    if (max_point > max_axis) {
      max_axis = max_point;
    }
  }
  min_axis -= 1;
  max_axis += 1;

  vec_t queue;
  init_vec(&queue);
  droplet_t *limit = malloc(sizeof(droplet_t));
  limit->x = min_axis;
  limit->y = min_axis;
  limit->z = min_axis;
  push_vec(&queue, limit);

  int droplet_area = 0;
  while (queue.size > 0) {
    droplet_t *droplet = pop_vec(&queue);

    vec_t *n = neighbours(droplet, min_axis, max_axis);

    for (int i = 0; i < n->size; i++) {
      droplet_t *exterior = get_vec(n, i);
      if (find_vec(&droplets, cmp_droplets, exterior) != NULL) {
        droplet_area += 1;
      } else {
        droplet_t *explore = malloc(sizeof(droplet_t));
        explore->x = exterior->x;
        explore->y = exterior->y;
        explore->z = exterior->z;
        push_vec(&queue, explore);
      }
    }

    for (int j = 0; j < n->size; j++) {
      free(get_vec(n, j));
    }
    free_vec(n);
    free(droplet);
  }

  for (int i = 0; i < droplets.size; i++) {
    free(get_vec(&droplets, i));
  }
  free_vec(&droplets);
  return droplet_area;
}

AOC_MAIN(d18, 4482, 2576)
#include "../common/headers.h"
#include "input/data.h"

#define CHAMBER_WIDTH 7
#define CHAMBER_HEIGHT 6500
#define FALLING_ROCK '@'
#define STOPPED_ROCK '#'

#define SPAWN_HYPHEN_SHAPE()                                                   \
  chamber[2][highest_rock - 3] = FALLING_ROCK;                                 \
  chamber[3][highest_rock - 3] = FALLING_ROCK;                                 \
  chamber[4][highest_rock - 3] = FALLING_ROCK;                                 \
  chamber[5][highest_rock - 3] = FALLING_ROCK;

#define SPAWN_PLUS_SHAPE()                                                     \
  chamber[3][highest_rock - 5] = FALLING_ROCK;                                 \
  chamber[2][highest_rock - 4] = FALLING_ROCK;                                 \
  chamber[3][highest_rock - 4] = FALLING_ROCK;                                 \
  chamber[4][highest_rock - 4] = FALLING_ROCK;                                 \
  chamber[3][highest_rock - 3] = FALLING_ROCK;

#define SPAWN_L_SHAPE()                                                        \
  chamber[4][highest_rock - 5] = FALLING_ROCK;                                 \
  chamber[4][highest_rock - 4] = FALLING_ROCK;                                 \
  chamber[4][highest_rock - 3] = FALLING_ROCK;                                 \
  chamber[3][highest_rock - 3] = FALLING_ROCK;                                 \
  chamber[2][highest_rock - 3] = FALLING_ROCK;

#define SPAWN_I_SHAPE()                                                        \
  chamber[2][highest_rock - 6] = FALLING_ROCK;                                 \
  chamber[2][highest_rock - 5] = FALLING_ROCK;                                 \
  chamber[2][highest_rock - 4] = FALLING_ROCK;                                 \
  chamber[2][highest_rock - 3] = FALLING_ROCK;

#define SPAWN_CUBE_SHAPE()                                                     \
  chamber[3][highest_rock - 4] = FALLING_ROCK;                                 \
  chamber[2][highest_rock - 4] = FALLING_ROCK;                                 \
  chamber[3][highest_rock - 3] = FALLING_ROCK;                                 \
  chamber[2][highest_rock - 3] = FALLING_ROCK;

bool rock_will_settle(int chamber[CHAMBER_WIDTH][CHAMBER_HEIGHT], int shift) {
  for (int y = CHAMBER_HEIGHT - 1; y >= 0; y--) {
    for (int x = 0; x < CHAMBER_WIDTH; x++) {
      if (chamber[x][y] == FALLING_ROCK) {
        if (shift == 0) {
          if (y == CHAMBER_HEIGHT - 1 || chamber[x][y + 1] == STOPPED_ROCK) {
            return true;
          }
        } else {
          if (x + shift < 0 || x + shift >= CHAMBER_WIDTH ||
              chamber[x + shift][y] == STOPPED_ROCK) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

void rock_fall(int chamber[CHAMBER_WIDTH][CHAMBER_HEIGHT]) {
  bool settle = rock_will_settle(chamber, 0);
  for (int y = CHAMBER_HEIGHT - 1; y >= 0; y--) {
    for (int x = 0; x < CHAMBER_WIDTH; x++) {
      if (chamber[x][y] == FALLING_ROCK) {
        if (settle) {
          chamber[x][y] = STOPPED_ROCK;
        } else {
          chamber[x][y] = 0;
          chamber[x][y + 1] = FALLING_ROCK;
        }
      }
    }
  }
}

void rock_push(int chamber[CHAMBER_WIDTH][CHAMBER_HEIGHT],
               iter_t *jet_pattern) {
  int shift = (char)(size_t)jet_pattern->value == '<' ? -1 : 1;
  bool settle = rock_will_settle(chamber, shift);

  for (int y = CHAMBER_HEIGHT - 1; y >= 0; y--) {
    if (shift == -1) {
      for (int x = 0; x < CHAMBER_WIDTH; x++) {
        if (chamber[x][y] == FALLING_ROCK && !settle) {
          chamber[x][y] = 0;
          chamber[x + shift][y] = FALLING_ROCK;
        }
      }
    } else {
      for (int x = CHAMBER_WIDTH - 1; x >= 0; x--) {
        if (chamber[x][y] == FALLING_ROCK && !settle) {
          chamber[x][y] = 0;
          chamber[x + shift][y] = FALLING_ROCK;
        }
      }
    }
  }

  iter_next_vec(jet_pattern);
}

void print_chamber(int chamber[CHAMBER_WIDTH][CHAMBER_HEIGHT]) {
  for (int y = 0; y < CHAMBER_HEIGHT; y++) {
    printf("|");
    for (int x = 0; x < CHAMBER_WIDTH; x++) {
      if (chamber[x][y] == FALLING_ROCK) {
        printf("%c", chamber[x][y]);
      } else if (chamber[x][y] == STOPPED_ROCK) {
        printf("%c", chamber[x][y]);
      } else {
        printf(".");
      }
    }
    printf("|\n");
  }
  printf("+-------+\n");
}

int challenge(char *input, int part) {
  int chamber[CHAMBER_WIDTH][CHAMBER_HEIGHT] = {0};
  vec_t jet_pattern;
  init_vec_with_capacity(&jet_pattern, 10100);
  fill_vec_str(&jet_pattern, input, NULL);

  iter_t iter = iter_begin_vec(&jet_pattern, true);
  int highest_rock = CHAMBER_HEIGHT - 1;
  long int rock_count = 0;
  int i = 0;
  while (true) {
    if (part == 1 && i >= 2022) {
      break;
    } else if (rock_count >= 1000000000000) {
      break;
    }

    switch (i % 5) {
    case 0:
      SPAWN_HYPHEN_SHAPE();
      rock_count += 4;
      break;
    case 1:
      SPAWN_PLUS_SHAPE();
      rock_count += 5;
      break;
    case 2:
      SPAWN_L_SHAPE();
      rock_count += 5;
      break;
    case 3:
      SPAWN_I_SHAPE();
      rock_count += 4;
      break;
    case 4:
      SPAWN_CUBE_SHAPE();
      rock_count += 4;
      break;
    }

    while (true) {
      rock_push(chamber, &iter);
      rock_fall(chamber);
      bool rocks_falling = false;
      for (int y = 0; y < CHAMBER_HEIGHT; y++) {
        for (int x = 0; x < CHAMBER_WIDTH; x++) {
          if (chamber[x][y] == FALLING_ROCK) {
            rocks_falling = true;
            break;
          }
        }
      }
      if (!rocks_falling) {
        break;
      }
    }

    for (int y = 0; y < CHAMBER_HEIGHT; y++) {
      for (int x = 0; x < CHAMBER_WIDTH; x++) {
        if (chamber[x][y] == STOPPED_ROCK && (y - 1) < highest_rock) {
          highest_rock = y - 1;
          break;
        }
      }
    }

    i++;
  }

  print_chamber(chamber);
  free_vec(&jet_pattern);
  return highest_rock;
}

int part1(char *input) { return challenge(input, 1); }

int part2(char *input) {
  // Left it running overnight
  return challenge(input, 2);
}

AOC_MAIN(d17, 3298, 12413999391794)
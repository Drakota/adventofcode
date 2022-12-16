#include "../common/headers.h"
#include "input/data.h"

#define LINE_TO_REPORT 2000000
#define LINE_TUNING_FREQUENCY 4000000

typedef struct sensor {
  int x;
  int y;
  struct {
    int x;
    int y;
  } closest_beacon;
  int distance_to_closest_beacon;
} sensor_t;

// Find the minimum and maximum x values of the sensors relative to the`
// distance of their closest beacon
#define FIND_MIN_MAX()                                                         \
  for (int i = 0; i < sensors.size; i++) {                                     \
    sensor_t *sensor = (sensor_t *)get_vec(&sensors, i);                       \
    if ((sensor->x + sensor->distance_to_closest_beacon) > max) {              \
      max = sensor->x + sensor->distance_to_closest_beacon;                    \
    }                                                                          \
    if ((sensor->x - sensor->distance_to_closest_beacon) < min) {              \
      min = sensor->x - sensor->distance_to_closest_beacon;                    \
    }                                                                          \
  }

int manhattan_distance(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}

void *parse_sensors(vec_t *vec, int index, char *token) {
  sensor_t *sensor = malloc(sizeof(sensor_t));
  sscanf(token,
         "Sensor at x=%d, y=%d: closest beacon is at x=%d, "
         "y=%d",
         &sensor->x, &sensor->y, &sensor->closest_beacon.x,
         &sensor->closest_beacon.y);
  sensor->distance_to_closest_beacon = manhattan_distance(
      sensor->x, sensor->y, sensor->closest_beacon.x, sensor->closest_beacon.y);
  return sensor;
}

int part1(char *input) {
  vec_t sensors;
  init_vec(&sensors);
  fill_vec_delim(&sensors, input, "\n", parse_sensors);

  int min = LINE_TO_REPORT;
  int max = 0;
  FIND_MIN_MAX();

  int positions = 0;
  while (min <= max) {
    for (int i = 0; i < sensors.size; i++) {
      sensor_t *sensor = (sensor_t *)get_vec(&sensors, i);
      if ((manhattan_distance(min, i, sensor->x, sensor->y) <=
           sensor->distance_to_closest_beacon) &&
          !((sensor->closest_beacon.y == LINE_TO_REPORT) &&
            sensor->closest_beacon.x == min)) {
        positions++;
        break;
      }
    }
    min++;
  }

  for (int i = 0; i < sensors.size; i++) {
    free(get_vec(&sensors, i));
  }
  free_vec(&sensors);
  return positions;
}

int part2(char *input) {
  vec_t sensors;
  init_vec(&sensors);
  fill_vec_delim(&sensors, input, "\n", parse_sensors);

  int min = LINE_TO_REPORT;
  int max = 0;
  FIND_MIN_MAX();

  int tuning_frequency = 0;
  while (min <= max) {
    for (int i = 0; i <= max; i++) {
      for (int j = 0; j < sensors.size; j++) {
        sensor_t *sensor = (sensor_t *)get_vec(&sensors, j);
        if ((manhattan_distance(min, j, sensor->x, sensor->y) <=
             sensor->distance_to_closest_beacon)) {
          i += sensor->distance_to_closest_beacon -
               manhattan_distance(min, i, sensor->x, sensor->y);
          break;
        }
        if (i == j) {
          tuning_frequency = min * LINE_TUNING_FREQUENCY + i;
          max = min - 1;
          break;
        }
      }
      min++;
    }
  }

  for (int i = 0; i < sensors.size; i++) {
    free(get_vec(&sensors, i));
  }
  free_vec(&sensors);
  return tuning_frequency;
}

AOC_MAIN(d15, 5838453, 12413999391794)
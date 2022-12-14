#include "../common/headers.h"
#include "input/data.h"

#define MAX_PACKET_LENGTH 512
#define DEBUG 0

bool compare_packet(char *packet_a, char *packet_b) {
  char packet_a_cpy[MAX_PACKET_LENGTH] = {};
  memcpy(packet_a_cpy, packet_a, strlen(packet_a));
  char packet_b_cpy[MAX_PACKET_LENGTH] = {};
  memcpy(packet_b_cpy, packet_b, strlen(packet_b));
  char *packet_a_ptr = &packet_a_cpy[0];
  char *packet_b_ptr = &packet_b_cpy[0];

  while (true) {
    if (*packet_a_ptr == '\0') {
      return true;
    } else if (*packet_b_ptr == '\0') {
      return false;
    }

    if (*packet_a_ptr == *packet_b_ptr) {
      packet_a_ptr++;
      packet_b_ptr++;
      continue;
    }

    if (*packet_a_ptr == '[' &&
        (*packet_b_ptr >= '1' && *packet_b_ptr <= '9')) {
      char temp[MAX_PACKET_LENGTH] = {'['};
      strncpy(temp + 1, packet_b_ptr, 1);
      temp[2] = ']';
      strncpy(temp + 3, packet_b_ptr + 1, MAX_PACKET_LENGTH - 3);
      sprintf(packet_b_ptr, "%s", temp);
      continue;
    } else if (*packet_b_ptr == '[' &&
               (*packet_a_ptr >= '1' && *packet_a_ptr <= '9')) {
      char temp[MAX_PACKET_LENGTH] = {'['};
      strncpy(temp + 1, packet_a_ptr, 1);
      temp[2] = ']';
      strncpy(temp + 3, packet_a_ptr + 1, MAX_PACKET_LENGTH - 3);
      sprintf(packet_a_ptr, "%s", temp);
      continue;
    }

    if (*packet_b_ptr == ']') {
      return false;
    } else if (*packet_a_ptr == ']') {
      return true;
    }

    if (atoi(packet_a_ptr) < atoi(packet_b_ptr)) {
      return true;
    }

    break;
  }
  return false;
}

void parse_packet_pair(char *token, int index, void *data) {
  int *packet_pair_index_sum = (int *)data;

  char packet_a[MAX_PACKET_LENGTH] = {};
  char packet_b[MAX_PACKET_LENGTH] = {};
  int first_packet = strchr(token, '\n') - token;
  strncpy(packet_a, token + 1, first_packet - 2);
  strncpy(packet_b, token + first_packet + 2,
          strchr(token, '\0') - (token + first_packet + 3));

  if (compare_packet(&packet_a[0], &packet_b[0])) {
    *packet_pair_index_sum += index;
  }
}

void fill_packet_vec(char *token, int index, void *data) {
  vec_t *packets = (vec_t *)data;
  if (strcmp(token, "")) {
    push_vec(packets, token);
  }
}

int part1(char *input) {
  int packet_pair_index_sum = 0;
  map_delim(input, "\n\n", parse_packet_pair, &packet_pair_index_sum);
  return packet_pair_index_sum;
}

int part2(char *input) {
  vec_t packets;
  init_vec(&packets);
  map_delim(input, "\n", fill_packet_vec, &packets);

  iter_t iter = window_begin_vec(&packets, 2);
  window_next_vec(&iter, 1);
  while (iter.value != NULL) {
    vec_t *window = (vec_t *)iter.value;
    char *packet_a = (char *)get_vec(window, 0);
    char *packet_b = (char *)get_vec(window, 1);

    if (!compare_packet(packet_a, packet_b)) {
      // Swap packets (bubble sort)
      set_vec(&packets, iter.index, packet_b);
      set_vec(&packets, iter.index + 1, packet_a);
    }
    window_next_vec(&iter, 1);
  }
  window_end_vec(&iter);

  int decoder_key = 1;
  for (int i = 0; i < packets.size; i++) {
    char *packet = (char *)get_vec(&packets, i);
    if (strncmp(packet, "[[0]]", 5) == 0) {
      decoder_key *= i + 1;
    } else if (strncmp(packet, "[[5]]", 5) == 0) {
      decoder_key *= i + 1;
    }
#if DEBUG
    printf("%s\n\n", (char *)get_vec(&packets, i));
#endif
  }

  free_vec(&packets);
  return decoder_key;
}

AOC_MAIN(d13, 5150, 23976)
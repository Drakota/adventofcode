#define AOC_MAIN(day, p1_answer, p2_answer)                                    \
  int main() {                                                                 \
    char *input = (char *)day##_input_data_txt;                                \
    unsigned int input_len = day##_input_data_txt_len;                         \
    char input_p1[input_len];                                                  \
    strncpy(input_p1, input, input_len);                                       \
    uint64_t p1 = part1(input_p1);                                             \
    if (p1 == p1_answer) {                                                     \
      printf(#day " p1 ✔\n");                                                  \
    } else {                                                                   \
      printf(#day " p1 ✗ - expected " #p1_answer ", got %lu\n", p1);           \
      exit(1);                                                                 \
    }                                                                          \
    char input_p2[input_len];                                                  \
    strncpy(input_p2, input, input_len);                                       \
    uint64_t p2 = part2(input_p2);                                             \
    if (p2 == p2_answer) {                                                     \
      printf(#day " p2 ✔\n");                                                  \
    } else {                                                                   \
      printf(#day " p2 ✗ - expected " #p2_answer ", got %lu\n", p2);           \
      exit(1);                                                                 \
    }                                                                          \
    return EXIT_SUCCESS;                                                       \
  }

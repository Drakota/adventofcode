typedef int make_iso_compilers_happy;

#define AOC_MAIN(day, p1_answer, p2_answer)                                    \
  int main() {                                                                 \
    unsigned char *input = day##_input_data_txt;                               \
    uint64_t p1 = part1(input);                                                \
    if (p1 == p1_answer) {                                                     \
      printf(#day " p1 ✔\n");                                                  \
    } else {                                                                   \
      printf(#day " p1 ✗ - expected " #p1_answer ", got %lu\n", p1);           \
      exit(1);                                                                 \
    }                                                                          \
    uint64_t p2 = part2(input);                                                \
    if (p2 == p2_answer) {                                                     \
      printf(#day " p2 ✔\n");                                                  \
    } else {                                                                   \
      printf(#day " p2 ✗ - expected " #p2_answer ", got %lu\n", p2);           \
      exit(1);                                                                 \
    }                                                                          \
    return EXIT_SUCCESS;                                                       \
  }

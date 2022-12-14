#include "../common/headers.h"
#include "input/data.h"

typedef struct cpu_state {
  int cycles;
  int register_x;
  int signal_strength;
  int crt_line;
  int part;
} cpu_state_t;

void check_cycles(cpu_state_t *cpu_state) {
  if (cpu_state->cycles == 20 || cpu_state->cycles == 60 ||
      cpu_state->cycles == 100 || cpu_state->cycles == 140 ||
      cpu_state->cycles == 180 || cpu_state->cycles == 220) {
    cpu_state->signal_strength += cpu_state->cycles * cpu_state->register_x;
  }
}

void draw_crt(cpu_state_t *cpu_state) {
  if (cpu_state->crt_line > 39) {
    cpu_state->crt_line = 0;
    printf("\n");
  }
  if (cpu_state->crt_line == cpu_state->register_x - 1 ||
      cpu_state->crt_line == cpu_state->register_x ||
      cpu_state->crt_line == cpu_state->register_x + 1) {
    printf("#");
  } else {
    printf(".");
  }
  cpu_state->crt_line++;
}

void execute_program(char *token, int index, void *data) {
  cpu_state_t *cpu_state = data;
  if (strcmp(token, "noop") == 0) {
    cpu_state->cycles++;
    cpu_state->part == 1 ? check_cycles(cpu_state) : draw_crt(cpu_state);
  } else {
    int arg;
    sscanf(token, "%*ms %d", &arg);
    for (int i = 0; i < 2; i++) {
      cpu_state->cycles++;
      cpu_state->part == 1 ? check_cycles(cpu_state) : draw_crt(cpu_state);
    }
    cpu_state->register_x += arg;
  }
}

int part1(char *input) {
  cpu_state_t cpu_state = {
      .cycles = 0,
      .register_x = 1,
      .part = 1,
  };
  map_delim(input, "\n", execute_program, &cpu_state);
  return cpu_state.signal_strength;
}

int part2(char *input) {
  cpu_state_t cpu_state = {
      .cycles = 0,
      .register_x = 1,
      .part = 2,
  };
  map_delim(input, "\n", execute_program, &cpu_state);
  printf("\n");
  return 0;
}

AOC_MAIN(d10, 14220, 0)
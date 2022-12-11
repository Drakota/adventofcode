#include "../common/headers.h"
#include "input/data.h"

typedef struct monkey {
  vec_t *items;
  struct {
    char *lhd;
    char op;
    char *rhd;
  } operation;
  struct {
    int cond;
    int monkey_index_true;
    int monkey_index_false;
  } branch;
} monkey_t;

void *parse_monkey(vec_t *vec, int index, char *token) {
  monkey_t *monkey = malloc(sizeof(monkey_t));
  monkey->items = malloc(sizeof(vec_t));
  init_vec(monkey->items);

  char *lines[6] = {};
  str_split(token, "\n", lines);

  int starting_items[10] = {};
  int count = sscanf(lines[1],
                     "  Starting items: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
                     &starting_items[0], &starting_items[1], &starting_items[2],
                     &starting_items[3], &starting_items[4], &starting_items[5],
                     &starting_items[6], &starting_items[7], &starting_items[8],
                     &starting_items[9]);

  for (int i = 0; i < count; i++) {
    push_vec(monkey->items, (void *)(size_t)starting_items[i]);
  }

  char *lhd;
  char op;
  char *rhd;
  sscanf(lines[2], "  Operation: new = %ms %c %ms", &lhd, &op, &rhd);

  monkey->operation.lhd = lhd;
  monkey->operation.op = op;
  monkey->operation.rhd = rhd;

  int cond;
  int monkey_index_true;
  int monkey_index_false;
  sscanf(lines[3], "  Test: divisible by %d", &cond);
  sscanf(lines[4], "    If true: throw to monkey %d", &monkey_index_true);
  sscanf(lines[5], "    If false: throw to monkey %d", &monkey_index_false);

  monkey->branch.cond = cond;
  monkey->branch.monkey_index_true = monkey_index_true;
  monkey->branch.monkey_index_false = monkey_index_false;

  return monkey;
}

int solution(char *input, int nb_rounds) {
  vec_t monkeys;
  init_vec(&monkeys);
  fill_vec_delim(&monkeys, input, "\n\n", parse_monkey);

  vec_t inspection_count;
  init_vec(&inspection_count);
  for (int i = 0; i < monkeys.size; i++) {
    push_vec(&inspection_count, (void *)0);
  }

  for (int round = 0; round < nb_rounds; round++) {
    for (int i = 0; i < monkeys.size; i++) {
      monkey_t *monkey = get_vec(&monkeys, i);

      int item;
      while ((item = (int)(size_t)pop_front_vec(monkey->items))) {
        set_vec(&inspection_count, i,
                (void *)((size_t)get_vec(&inspection_count, i)) + 1);

        int worry_level = 0;
        if (strcmp(monkey->operation.lhd, "old") == 0) {
          worry_level = item;
        }

        int rhd = 0;
        if (strcmp(monkey->operation.rhd, "old") == 0) {
          rhd = item;
        } else {
          rhd = atoi(monkey->operation.rhd);
        }

        if (monkey->operation.op == '+') {
          worry_level += rhd;
        } else if (monkey->operation.op == '-') {
          worry_level -= rhd;
        } else if (monkey->operation.op == '*') {
          worry_level *= rhd;
        } else if (monkey->operation.op == '/') {
          worry_level /= rhd;
        }
        if (nb_rounds == 20) {
          worry_level /= 3;
        }

        int index = worry_level % monkey->branch.cond == 0
                        ? monkey->branch.monkey_index_true
                        : monkey->branch.monkey_index_false;
        push_vec(((monkey_t *)get_vec(&monkeys, index))->items,
                 (void *)(size_t)worry_level);
      }
    }
  }

  sort_vec(&inspection_count, sort_descending);

  int monkey_business = (size_t)get_vec(&inspection_count, 0) *
                        (size_t)get_vec(&inspection_count, 1);

  free_vec(&inspection_count);
  for (int i = 0; i < monkeys.size; i++) {
    monkey_t *monkey = get_vec(&monkeys, i);
    free_vec(monkey->items);
    free(monkey->operation.lhd);
    free(monkey->operation.rhd);
    free(monkey->items);
    free(monkey);
  }
  free_vec(&monkeys);
  return monkey_business;
}

int part1(char *input) { return solution(input, 20); }

int part2(char *input) { return solution(input, 10000); }

AOC_MAIN(d11, 101760, 1132484162)
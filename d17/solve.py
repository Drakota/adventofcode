from os.path import dirname, join
from re import findall
import collections
from itertools import product

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

lines = file.read().splitlines()


def simulate(dimension):
    active_cubes = {
        (i, j) + (0,) * dimension
        for i, line in enumerate(lines)
        for j, cube in enumerate(line)
        if cube == "#"
    }

    def is_in_cycle_range(cycle_range):
        length = len(
            active_cubes
            & set(product(*[range(cycle - 1, cycle + 2) for cycle in cycle_range]))
        )
        return cycle_range in active_cubes and length == 4 or length == 3

    for cycle in range(6):
        active_cubes = set(
            filter(
                is_in_cycle_range,
                product(range(-cycle - 1, cycle + 8), repeat=2 + dimension),
            )
        )

    return len(active_cubes)


# Part 1
print(simulate(1))

# Part 2
print(simulate(2))

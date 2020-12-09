from os.path import dirname, join
import re

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

sequence = [int(number) for number in file.read().splitlines()]
preamble_size = 25
encryption_weakness = None


def sum_of_two(preamble, result):
    for number in preamble:
        if result - number in preamble:
            return True
    return False


# Part 1
for i in range(len(sequence)):
    preamble = sequence[i : preamble_size + i + 1]
    result = sequence[preamble_size + i + 1]
    if not sum_of_two(preamble, result):
        encryption_weakness = result
        print(encryption_weakness)
        break

# Part 2
i = 0
offset = 0
arr = list()
while i < len(sequence):
    arr.append(sequence[i])
    i += 1
    if sum(arr) == encryption_weakness:
        print(min(arr) + max(arr))
        break
    elif sum(arr) > encryption_weakness:
        arr = list()
        offset += 1
        i = offset

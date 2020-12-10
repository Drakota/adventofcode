from os.path import dirname, join
import collections

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

adapters = sorted([int(number) for number in file.read().splitlines()])
# Add initial 0 jolt adapter and builtin adapter that is 3 jolt higher than the max
adapters = [0] + adapters + [max(adapters) + 3]

# Part 1
differences = {1: 0, 3: 0}
for i in range(len(adapters) - 1):
    differences[adapters[i + 1] - adapters[i]] += 1
print(differences[1] * differences[3])

memo = {}


def arrangements(i):
    if i == len(adapters) - 1:
        return 1
    if i in memo:
        return memo[i]

    total = 0
    for j in range(i + 1, len(adapters)):
        if adapters[j] - adapters[i] <= 3:
            total += arrangements(j)
    memo[i] = total
    return total


# Part 2
print(arrangements(0))
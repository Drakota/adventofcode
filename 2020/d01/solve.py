from os.path import dirname, join

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

sum = 2020
arr = [int(num) for num in file.read().splitlines()]


def solve(sum, depth):
    if depth == 1:
        return sum
    for num in arr:
        res = None
        needle = sum - num
        if depth > 2:
            res = solve(needle, depth - 1)
        elif needle in arr:
            res = solve(needle, depth - 1)
        if res is None:
            continue
        return res * num


print(f"Depth 2: {solve(sum, 2)}")
print(f"Depth 3: {solve(sum, 3)}")

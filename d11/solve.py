from os.path import dirname, join
import copy

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

lines = [list(row) for row in file.read().splitlines()]


def find_neighbours(row, column, floor):
    neighbours = 0
    positions = [(1, 0), (-1, 0), (0, 1), (0, -1), (1, 1), (1, -1), (-1, 1), (-1, -1)]

    for x, y in positions:
        n, m = row + y, column + x
        if 0 <= n < len(floor) and 0 <= m < len(floor[n]):
            neighbours += 1 if floor[n][m] == "#" else 0
    return neighbours


def find_neighbours_ray(row, column, floor):
    neighbours = 0

    for x in (-1, 0, 1):
        for y in (-1, 0, 1):
            for i in range(len(floor)):
                n, m = row + i * y, column + i * x
                if n == row and m == column:
                    continue
                if (
                    0 <= n < len(floor)
                    and 0 <= m < len(floor[n])
                    and floor[n][m] != "."
                ):
                    neighbours += 1 if floor[n][m] == "#" else 0
                    break
    return neighbours


def step(method, tolerance, floor):
    temp = copy.deepcopy(floor)
    for row in range(len(floor)):
        for column in range(len(floor[row])):
            if temp[row][column] == ".":
                continue
            neighbours = method(row, column, floor)
            if neighbours == 0:
                temp[row][column] = "#"
            elif neighbours >= tolerance:
                temp[row][column] = "L"

    return temp, sum([row.count("#") for row in temp])


def simulate(method, tolerance):
    grid = copy.deepcopy(lines)
    occupied = 0
    while True:
        grid, count = step(method, tolerance, grid)
        if occupied == count:
            return occupied
        occupied = count


# Part 1
print(simulate(find_neighbours, 4))

# Part 2
print(simulate(find_neighbours_ray, 5))
from os.path import dirname, join

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

grid = []
for line in file.read().splitlines():
    grid.append(line)


def descend(hsteps, vsteps):
    x = y = obstacles = 0
    while y + 1 < len(grid):
        x += hsteps
        y += vsteps
        if grid[y][x % len(grid[y])] == "#":
            obstacles += 1
    return obstacles


# Part 1
print(descend(3, 1))

# Part 2
slopes = [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)]
ans = 1
for slope in slopes:
    ans *= descend(*slope)
print(ans)
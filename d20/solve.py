from os.path import dirname, join
from copy import deepcopy

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

tiles = {
    int(tile.splitlines()[0].split()[1][:-1]): list(map(list, tile.splitlines()[1:]))
    for tile in file.read().split("\n\n")
}


def flip(tile):
    temp = []
    for line in tile:
        temp.append(line[::-1])
    return temp


def rotate(tile, degrees=90):
    temp = tile
    for _ in range(int(degrees / 90)):
        temp = list(zip(*temp[::-1]))
    return temp


def edges(tile):
    # fmt: off
    return [
        tile[0][0], tile[0][-1],
        tile[-1][0], tile[-1][-1]
    ]
    # fmt: on


def add_to_grid(grid, tile, coords):
    x, y = coords
    if 0 <= x and 0 <= y:
        if x >= len(grid):
            grid.append([tile])
            return True
        else:
            grid[x].append(tile)
            return True
    return False


def find_arrangement(grid, tiles_left, id, tile):
    if len(grid) == 0:
        grid.append([tile])
        temp = deepcopy(tiles_left)
        del temp[id]
        solve(grid, temp)
    else:
        for i, row in enumerate(grid):
            for j, column in enumerate(row):
                if (
                    edges(column)[0] == edges(tile)[2]
                    and edges(column)[1] == edges(tile)[3]
                ):
                    if add_to_grid(grid, tile, (i - 1, j)):
                        temp = deepcopy(tiles_left)
                        del temp[id]
                        solve(grid, temp)
                elif (
                    edges(column)[1] == edges(tile)[0]
                    and edges(column)[3] == edges(tile)[2]
                ):
                    if add_to_grid(grid, tile, (i, j + 1)):
                        temp = deepcopy(tiles_left)
                        del temp[id]
                        solve(grid, temp)
                elif (
                    edges(column)[2] == edges(tile)[0]
                    and edges(column)[3] == edges(tile)[1]
                ):
                    if add_to_grid(grid, tile, (i + 1, j)):
                        temp = deepcopy(tiles_left)
                        del temp[id]
                        solve(grid, temp)
                elif (
                    edges(column)[0] == edges(tile)[1]
                    and edges(column)[2] == edges(tile)[3]
                ):
                    if add_to_grid(grid, tile, (i, j - 1)):
                        temp = deepcopy(tiles_left)
                        del temp[id]
                        solve(grid, temp)


def solve(grid, tiles_left):
    if sum([len(row) for row in grid]) == len(tiles):
        return grid
    for id, tile in tiles_left.items():
        for degree in [0, 90, 180, 270]:
            find_arrangement(grid, tiles_left, id, rotate(tile, degree))
            find_arrangement(grid, tiles_left, id, flip(rotate(tile, degree)))


# Part 1
print(solve([], deepcopy(tiles)))
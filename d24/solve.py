from os.path import dirname, join
from re import findall
from collections import defaultdict

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

tiles = file.read().splitlines()

vectors = {
    "e": (1, 0),
    "se": (0, -1),
    "sw": (-1, -1),
    "w": (-1, 0),
    "nw": (0, 1),
    "ne": (1, 1),
}

tiles_to_flip = defaultdict(int)
for tile in tiles:
    directions = findall("e|se|sw|w|nw|ne", tile)
    ref_x, ref_y = 0, 0

    for direction in directions:
        dir_vector = vectors[direction]
        ref_x += dir_vector[0]
        ref_y += dir_vector[1]
    tiles_to_flip[(ref_x, ref_y)] += 1


# Part 1
print(len(dict(filter(lambda item: item[1] % 2 == 1, tiles_to_flip.items()))))


def step(tiles):
    neighbors = defaultdict(int)
    for coords, flips in tiles.items():
        if flips % 2 == 0:
            continue
        for vector in vectors.values():
            neighbors[(coords[0] + vector[0], coords[1] + vector[1])] += 1

    to_flip = {}
    for coords, flips in tiles.items():
        if flips % 2 == 1:
            if neighbors.get(coords, 0) not in (1, 2):
                pass
            else:
                to_flip[coords] = 1
    for coords, flips in neighbors.items():
        if flips == 2 and tiles.get(coords, 0) % 2 == 0:
            to_flip[coords] = 1
    return to_flip


for _ in range(100):
    tiles_to_flip = step(tiles_to_flip)

# Part 2
print(len(dict(filter(lambda item: item[1] % 2 == 1, tiles_to_flip.items()))))
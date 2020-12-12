from os.path import dirname, join
import copy

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

instructions = [(line[0], int(line[1:])) for line in file.read().splitlines()]


def navigate():
    x, y = 0, 0
    directions = ["E", "S", "W", "N"]
    facing = 0

    for command, units in instructions:
        if command == "F":
            command = directions[facing]
        if command == "R":
            facing = (facing + int(units / 90)) % 4
        elif command == "L":
            facing = (facing + -int(units / 90)) % 4
        elif command == "E":
            x += units
        elif command == "W":
            x -= units
        elif command == "N":
            y += units
        elif command == "S":
            y -= units
    return abs(x) + abs(y)


def navigate_waypoint():
    x, y = 0, 0
    wx, wy = 10, 1

    for command, units in instructions:
        if command == "F":
            x += wx * units
            y += wy * units
        if command == "R":
            turns = int(units / 90)
            while turns:
                wx, wy = wy, -wx
                turns -= 1
        elif command == "L":
            turns = int(units / 90)
            while turns:
                wx, wy = -wy, wx
                turns -= 1
        elif command == "E":
            wx += units
        elif command == "W":
            wx -= units
        elif command == "N":
            wy += units
        elif command == "S":
            wy -= units
    return abs(x) + abs(y)


# Part 1
print(navigate())

# Part 2
print(navigate_waypoint())
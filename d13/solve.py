from os.path import dirname, join
from math import prod

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

lines = file.read().splitlines()
timestamp = int(lines[0])
buses = [int(bus) for bus in lines[1].split(",") if bus != "x"]

# Part 1
print(prod(min((bus - timestamp % bus, bus) for bus in buses)))

buses = [(i, int(bus)) for i, bus in enumerate(lines[1].split(",")) if bus != "x"]

time, step = 0, 1
for index, bus in buses:
    while (time + index) % bus:
        time += step
    step *= bus

# Part 2
print(time)
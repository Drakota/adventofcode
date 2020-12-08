from os.path import dirname, join
import re

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

lines = file.read().split("\n")

container = {}
contains = {}

for line in lines:
    bag = line.split("bags contain")
    color = bag[0].strip()
    inner_bags = bag[1].strip()
    for inner_count, inner_color in re.findall(r"(\d+) (.+?) bags?[,.]", inner_bags):
        if inner_color not in container:
            container[inner_color] = set()
        if color not in contains:
            contains[color] = list()
        container[inner_color].add(color)
        contains[color].append((int(inner_count), inner_color))


golden_hold = set()


def traverse_bags(color):
    if color not in container:
        return
    for inner_color in container[color]:
        golden_hold.add(inner_color)
        traverse_bags(inner_color)


traverse_bags("shiny gold")

# Part 1
print(len(golden_hold))


def calculate_gold_cost(color):
    total = 0
    if color not in contains:
        return total
    for inner_count, inner_color in contains[color]:
        total += inner_count
        total += inner_count * calculate_gold_cost(inner_color)
    return total


# Part 2
print(calculate_gold_cost("shiny gold"))
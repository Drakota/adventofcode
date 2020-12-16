from os.path import dirname, join
from re import findall
import math

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

lines = file.read().splitlines()

rules = {
    k: [list(map(int, d.split("-"))) for d in v]
    for (k, v) in {
        r.split(":")[0]: findall(r"(\d+-\d+)", r.split(":")[1]) for r in lines[:20]
    }.items()
}
ticket = [int(d) for d in lines[22].split(",")]
nearby_tickets = [[int(d) for d in t] for t in [v.split(",") for v in lines[25:]]]


def valid_field(field):
    return any(a <= field <= b for rule in rules.values() for a, b in rule)


invalid_fields_sum = 0
for ticket in nearby_tickets:
    for field in ticket:
        if not valid_field(field):
            invalid_fields_sum += field

valid_tickets = [t for t in nearby_tickets if all(valid_field(f) for f in t)]
possible_matching_rules = {}
for i in range(len(ticket)):
    possible_matching_rules[i] = set()
    for name, rule in rules.items():
        if all(any(start <= t[i] <= end for start, end in rule) for t in valid_tickets):
            possible_matching_rules[i].add(name)

ordered_rules = {}
while possible_matching_rules:
    i = next(i for i, s in possible_matching_rules.items() if len(s) == 1)
    ordered_rules[i] = next(iter(possible_matching_rules[i]))
    del possible_matching_rules[i]
    for j in possible_matching_rules:
        possible_matching_rules[j].discard(ordered_rules[i])

# Part 1
print(invalid_fields_sum)

# Part 2
print(math.prod(n for i, n in enumerate(ticket) if ordered_rules[i].startswith("departure")))
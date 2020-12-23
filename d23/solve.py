from os.path import dirname, join
from re import findall

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

cups = [int(cup) for cup in file.read()]


def move(cups, active):
    cups_length = len(cups)

    pickup = []
    for i in [(cups.index(active) + i + 2) % cups_length for i in range(3)]:
        pickup.append(cups[i])

    for i in pickup:
        cups.remove(i)

    dest = active - 1
    while dest not in cups:
        dest -= 1
        if dest < min(cups):
            dest = max(cups)

    dest_index = cups.index(dest)
    insert_index = (dest_index + 1) % cups_length

    cups = cups[:insert_index] + pickup + cups[insert_index:]
    new_active = cups[(cups.index(active) + 1) % cups_length]

    return cups, new_active


active = cups[0]
for i in range(100):
    cups, active = move(cups, active)

# Part 1
print("".join([str(cup) for cup in cups]))

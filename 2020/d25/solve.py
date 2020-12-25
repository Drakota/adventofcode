from os.path import dirname, join

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

lines = file.read().splitlines()
card_pk = int(lines[0])
door_pk = int(lines[1])
subject_number = 7


def find_loop_size(pk):
    loop_size = 1
    while pow(subject_number, loop_size, 20201227) != card_pk:
        loop_size += 1
    return loop_size


# Part 1
print(pow(door_pk, find_loop_size(card_pk), 20201227))
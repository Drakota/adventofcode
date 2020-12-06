from os.path import dirname, join
from re import sub

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

answers = file.read().split("\n\n")

unique_answers = 0
same_answers = 0
for line in answers:
    unique_answers += len(set(line.replace("\n", "")))
    groups = line.split()
    union = groups[0]
    for group in groups:
        union = set(union) & set(group)
    same_answers += len(union)

# Part 1
print(unique_answers)

# Part 2
print(same_answers)
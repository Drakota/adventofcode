from os.path import dirname, join
from re import findall

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

numbers = [int(number) for number in file.read().split(",")]


def spoken(end):
    memory = {numbers[i]: i + 1 for i in range(len(numbers))}
    number = 0
    for i in range(len(memory) + 1, end):
        if number in memory:
            memory[number], number = i, i - memory[number]
        else:
            memory[number] = i
            number = 0
    return number


# Part 1
print(spoken(2020))

# Part 2
print(spoken(30000000))

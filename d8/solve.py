from os.path import dirname, join
import re

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

instructions = file.read().splitlines()


def run(program, return_acc=True):
    acc = 0
    pc = 0
    executed = set()
    while True:
        if pc == len(program):
            return acc
        if pc in executed:
            return acc if return_acc else None

        line = program[pc]
        instruction, argument = line.split()

        executed.add(pc)
        if instruction == "jmp":
            pc += int(argument)
        elif instruction == "acc":
            acc += int(argument)
            pc += 1
        elif instruction == "nop":
            pc += 1


# Part 1
print(run(instructions))

# Part 2
for i in range(len(instructions)):
    program = list(instructions)
    if "nop" in program[i]:
        program[i] = program[i].replace("nop", "jmp")
    elif "jmp" in program[i]:
        program[i] = program[i].replace("jmp", "nop")
    res = run(program, False)
    if res:
        print(res)

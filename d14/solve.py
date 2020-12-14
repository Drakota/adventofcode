from os.path import dirname, join
from re import findall

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

instructions = file.read().splitlines()


def get_all_addr(addr_mask):
    if "X" in addr_mask:
        for bit in ["0", "1"]:
            yield from get_all_addr(addr_mask.replace("X", bit, 1))
    else:
        yield int(addr_mask, 2)


def run(write_all_mem_addr=False):
    mask = None
    memory = {}

    for instruction in instructions:
        if "mask" in instruction:
            mask = list(instruction.split()[2])
        else:
            instruction = instruction.split()
            addr = int(findall(r"\[(.+?)\]", instruction[0])[0])
            if write_all_mem_addr:
                addr_mask = list("{:036b}".format(addr))
                for index, value in enumerate(mask):
                    addr_mask[index] = value if value != "0" else addr_mask[index]
                for a in get_all_addr("".join(addr_mask)):
                    memory[a] = int(instruction[2])
            else:
                write = list("{:036b}".format(int(instruction[2])))
                for index, value in enumerate(mask):
                    write[index] = value if value != "X" else write[index]
                    res = int("".join(write), 2)
                memory[addr] = res
    return sum(memory.values())


# Part 1
print(run())

# Part 2
print(run(True))

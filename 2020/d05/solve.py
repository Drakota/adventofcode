from os.path import dirname, join
from re import sub

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")


def binary_search(arr, code, lh, up):
    if len(code) != 0 and code[0] == lh:
        return binary_search(arr[0 : int(len(arr) / 2)], code[1:], lh, up)
    elif len(code) != 0 and code[0] == up:
        return binary_search(arr[int(len(arr) / 2) : len(arr)], code[1:], lh, up)
    else:
        return arr[0]


seat_ids = set()
for line in file.read().splitlines():
    row = binary_search(list(range(0, 128)), line, "F", "B")
    column = binary_search(list(range(0, 8)), sub("[FB]", "", line), "L", "R")
    seat_ids.add(row * 8 + column)

# Part 1
print(max(seat_ids))

# Part 2
for seat_id in range(256 * 8):
    if seat_id not in seat_ids and seat_id + 1 in seat_ids and seat_id - 1 in seat_ids:
        print(seat_id)

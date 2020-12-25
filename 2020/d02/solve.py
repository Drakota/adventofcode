from os.path import dirname, join
import re

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

valid_passwd_p1 = 0
valid_passwd_p2 = 0
for line in file.read().splitlines():
    lbound, rbound, char, passwd = re.findall("\\w+", line)
    # Part 1
    if passwd.count(char) >= int(lbound) and passwd.count(char) <= int(rbound):
        valid_passwd_p1 += 1
    # Part 2
    if bool(passwd[int(lbound) - 1] == char) ^ bool(passwd[int(rbound) - 1] == char):
        valid_passwd_p2 += 1

print(f"Part 1: {valid_passwd_p1}")
print(f"Part 2: {valid_passwd_p2}")
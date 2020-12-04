from os.path import dirname, join
import re

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

passports = []
required_fields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"]
colors = ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]
valid_passports_p1 = 0
valid_passports_p2 = 0


def in_range(value, lbound, rbound):
    value = int(value)
    return lbound <= value <= rbound


def valid_height(value):
    if "cm" in value:
        value = int(value.replace("cm", ""))
        if not in_range(value, 150, 193):
            return False
    elif "in" in value:
        value = int(value.replace("in", ""))
        if not in_range(value, 59, 76):
            return False
    else:
        return False
    return True


def validate(name, value):
    if name == "byr" and not in_range(value, 1920, 2002):
        return False
    elif name == "iyr" and not in_range(value, 2010, 2020):
        return False
    elif name == "eyr" and not in_range(value, 2020, 2030):
        return False
    elif name == "hgt" and not valid_height(value):
        return False
    elif name == "hcl" and not re.match("^\\#[a-zA-Z0-9]{6}$", value):
        return False
    elif name == "ecl" and not any(color in value for color in colors):
        return False
    elif name == "pid" and len(value) != 9 and not isinstance(value, int):
        return False
    elif name == "cid":
        pass
    return True


for line in file.read().split("\n\n"):
    passports.append(line)

for passport in passports:
    if all(required_field in passport for required_field in required_fields):
        valid_passports_p1 += 1
        fields = passport.split()
        if all(validate(*field.split(":")) for field in fields):
            valid_passports_p2 += 1

# Part 1
print(valid_passports_p1)

# Part 2
print(valid_passports_p2)
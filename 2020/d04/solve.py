from os.path import dirname, join
from re import match

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

passports = file.read().split("\n\n")
rules = {
    "byr": lambda value: 1920 <= int(value) <= 2002,
    "iyr": lambda value: 2010 <= int(value) <= 2020,
    "eyr": lambda value: 2020 <= int(value) <= 2030,
    "hgt": lambda value: bool(
        match("^(1[5-8][0-9]|19[0-3])(cm)$|^(59|6[0-9]|7[0-6])(in)$", value)
    ),
    "hcl": lambda value: bool(match("^#[a-zA-Z0-9]{6}$", value)),
    "ecl": lambda value: value in ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"],
    "pid": lambda value: len(value) == 9 and value.isnumeric(),
    "cid": lambda value: True,
}

valid_passports_p1 = valid_passports_p2 = 0
for passport in passports:
    if all(
        required_field in passport
        for required_field in {k: rules[k] for k in rules.keys() - {"cid"}}
    ):
        valid_passports_p1 += 1
        fields = list(x.split(":") for x in passport.split())
        if all(list(rules[name](value) for name, value in fields)):
            valid_passports_p2 += 1

# Part 1
print(valid_passports_p1)

# Part 2
print(valid_passports_p2)
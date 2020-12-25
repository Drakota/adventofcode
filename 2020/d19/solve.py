from os.path import dirname, join

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

lines = file.read().splitlines()
rules = {
    int(name): [list(map(int, r.strip().split())) for r in rule.split("|")]
    for name, rule in [line.split(":") for line in lines[:133] if '"' not in line]
}
character_rules = {
    int(name): rule.strip().replace('"', "")
    for name, rule in [line.split(":") for line in lines[:133] if '"' in line]
}
messages = lines[134:]
memo = {}


def validate_ruleset(message, start, end, rules):
    if start == end and not rules:
        return True
    if start == end or not rules:
        return False

    valid = False
    for i in range(start + 1, end + 1):
        if validate(message, start, i, rules[0]) and validate_ruleset(
            message, i, end, rules[1:]
        ):
            valid = True

    return valid


def validate(message, start, end, rule_number):
    key = (start, end, rule_number)
    if key in memo:
        return memo[key]

    valid = False
    if rule_number in character_rules:
        valid = message[start:end] == character_rules[rule_number]
    else:
        for rule in rules[rule_number]:
            if validate_ruleset(message, start, end, rule):
                valid = True

    memo[key] = valid
    return valid


def valid_messages(p2=False):
    valid = 0
    if p2:
        rules[8] = [[42], [42, 8]]
        rules[11] = [[42, 31], [42, 11, 31]]
    for message in messages:
        memo.clear()
        if validate(message, 0, len(message), 0):
            valid += 1
    return valid


# Part 1
print(valid_messages())

# Part 2
print(valid_messages(True))

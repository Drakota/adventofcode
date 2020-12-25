from os.path import dirname, join
from re import sub

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

expressions = file.read().splitlines()


class Term(int):
    def __mul__(self, other):
        return Term(int(self) + other)

    def __add__(self, other):
        return Term(int(self) + other)

    def __sub__(self, other):
        return Term(int(self) * other)


def evaluate(expression, add_before_mul=False):
    expression = sub(r"(\d+)", r"Term(\1)", expression)
    expression = expression.replace("*", "-")
    if add_before_mul:
        expression = expression.replace("+", "*")
    return eval(expression, {}, {"Term": Term})


# Part 1
print(sum(evaluate(expression) for expression in expressions))

# Part 2
print(sum(evaluate(expression, True) for expression in expressions))
from os.path import dirname, join
from re import findall

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

recipes = [
    [ingredients.strip().split(), [a.strip() for a in allergens.strip().split(",")]]
    for (ingredients, allergens) in [
        findall(r"(.*)\(contains (.*)\)", line)[0] for line in file.read().splitlines()
    ]
]
all_ingredients = [
    ingredient for ingredients, _ in recipes for ingredient in ingredients
]

possible_ingredients = {}

for ingredients, allergens in recipes:
    for allergen in allergens:
        if allergen not in possible_ingredients:
            possible_ingredients[allergen] = set(ingredients)
        else:
            possible_ingredients[allergen] &= set(ingredients)

all_possible_ingredients = [
    ingredient
    for ingredients in possible_ingredients.values()
    for ingredient in ingredients
]

identified_ingredients = {}
while possible_ingredients:
    for allergen, ingredients in possible_ingredients.items():
        if len(ingredients) == 1:
            identified_ingredients[list(ingredients)[0]] = allergen
            del possible_ingredients[allergen]
            break
        elif any(
            ingredient in ingredients
            for ingredient in list(identified_ingredients.keys())
        ):
            possible_ingredients[allergen] -= identified_ingredients.keys()


# Part 1
print(
    sum([ingredient not in all_possible_ingredients for ingredient in all_ingredients])
)

# Part 2
print(",".join(sorted(identified_ingredients, key=identified_ingredients.get)))
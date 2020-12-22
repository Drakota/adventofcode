from os.path import dirname, join
from re import findall
from copy import deepcopy

current_dir = dirname(__file__)
file_path = join(current_dir, "input/data.txt")
file = open(file_path, "r")

decks = file.read().split("\n\n")
p1deck = [int(card) for card in decks[0].split()[2:]]
p2deck = [int(card) for card in decks[1].split()[2:]]


def play(deck1, deck2, recursive=False):
    rounds = set()
    deck1 = deepcopy(deck1)
    deck2 = deepcopy(deck2)

    while len(deck1) != 0 and len(deck2) != 0:
        key = (tuple(deck1), tuple(deck2))
        if key in rounds:
            return True, deck1
        rounds.add(key)

        card1, card2 = deck1.pop(0), deck2.pop(0)
        winner = card1 > card2
        if recursive and (card1 <= len(deck1) and card2 <= len(deck2)):
            winner, _ = play(deck1[:card1], deck2[:card2], True)
        if winner:
            deck1 += [card1, card2]
        else:
            deck2 += [card2, card1]

    return len(deck1) != 0, deck1 if len(deck1) != 0 else deck2


def score(deck):
    return sum([deck[i] * (len(deck) - i) for i in range(len(deck))])


# Part 1
print(score(play(p1deck, p2deck)[1]))

# Part 2
print(score(play(p1deck, p2deck, True)[1]))
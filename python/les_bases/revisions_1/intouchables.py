#!/usr/bin/env python
# -*- coding: utf-8 -*-
from math import ceil, sqrt
from sys import argv
from color_print import cprint

def somme_div(y):
    upper = ceil(sqrt(y))+1
    diviseurs = [x for x in range(1, upper) if (y % x == 0)]
    return sum(diviseurs)


def intouchable(x):
    for y in range(2, x ** 2):
        if x == somme_div(y):
            return False
    return True

def test():
    print("Nombres intouchables : ", end="")

    if not intouchable(4) and not intouchable(16) and intouchable(5) and all(not intouchable(x) for x in range(7, 125, 2)):
        cprint("PASS", 'blue')
    else:
        cprint("FAIL", 'red')


if __name__ == "__main__":
    if len(argv) == 2 and argv[1] == "test":
        test()
    else:
        x = input("Number to test (between 0 and 125)?\n>>> ")
        try:
            x = int(x)
            if not (0 < x <= 125):
                raise ValueError

        except ValueError:
            print("Error: couldn't parse", x, "as an integer")

        if intouchable(x):
            print(x, "est intouchable")
        else:
            print(x, "n'est pas intouchable")
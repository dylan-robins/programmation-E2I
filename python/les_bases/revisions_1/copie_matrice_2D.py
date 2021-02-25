#!/usr/bin/env python
# -*- coding: utf-8 -*-
from color_print import cprint

def transpose_matrix(m1, m2):
    for y, row in enumerate(m1):
        x = 0
        while x < len(row):
            m2[len(row)-1 - x][len(m1)-1 - y] = row[x]
            x += 1

def test():
    print("Testing matrix transposition : ", end="")
    m1 = [
        [1, 2, 3],
        [4, 5, 6]
    ]
    m2 = [[None for x in range(2)] for y in range(3)]
    ref = [
        [6, 3],
        [5, 2],
        [4, 1]
    ]

    transpose_matrix(m1, m2)

    if m2 == ref:
        cprint("PASS", 'blue')
    else:
        cprint("FAIL", 'red')

if __name__ == "__main__":
    test()
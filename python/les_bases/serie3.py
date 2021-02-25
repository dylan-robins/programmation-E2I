#!/usr/bin/env python
# -*- coding: utf-8 -*-
def quantieme_2020():
    nb_jours = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    
    mois = int(input("Entrez le mois [1-12]: >>> "))
    assert (1 <= mois <= 12), "Mois incorrect"
    jour = int(input(f"Entrez le jour [1-{nb_jours[mois-1]}]: >>> "))
    assert (1 <= jour <= nb_jours[mois-1]), "Jour incorrect"

    quantieme = sum(nb_jours[:mois-1]) + jour
    print(f"Quantième de la date {jour:02d}/{mois:02d}/2020: {quantieme}")

def reverse_table_construction(n):
    tab = []
    for _ in range(n):
        num = int(input("Enter an integer: >>> "))
        tab.insert(0, num)

    print("tab:", tab)
    print("Even elements of tab:", [elem for elem in tab if (elem % 2 == 0)])
    print("Elements at odd indices of tab:", [elem for i,elem in enumerate(tab) if (i % 2 == 1)])

    x = int(input("Enter an integer to search for: >>> "))
    if x in tab:
        print(x, "is in tab at index", tab.index(x))
    else:
        print(x, "isn't in tab")
    
    print("Min value in tab:", min(tab))

def create_2d_array(N=2, M=3):
    matrix = [[None for x in range(N)] for y in range(M)]

    y = 0
    while y < M:
        x = 0
        while x < N:
            val = input(f"Enter the value of matrix cell ({x},{y}): >>> ")
            matrix[y][x] = val
            x += 1
        y += 1
    print("Matrix :")
    print_matrix(matrix)

def print_matrix(matrix):
    for row in matrix:
        print("| ", end="")
        for val in row:
            print(val, end=" | ")
        print("")

if __name__ == "__main__":
    print("Test quantieme_2020...")
    quantieme_2020()
    print("Test create_2d_array...")
    create_2d_array()
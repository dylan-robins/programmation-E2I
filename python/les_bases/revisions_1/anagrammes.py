#!/usr/bin/env python
# -*- coding: utf-8 -*-
from color_print import cprint

def fact(n):
    f = n
    while n > 1:
        n -= 1
        f *= n
    return f


def anagramme_pos(ch, pos):
    if pos == 0:
        anagrammes = [
            ch[0] + ch[1] + ch[2],
            ch[0] + ch[2] + ch[1]
        ]
    elif pos == 1:
        anagrammes = [
            ch[1] + ch[0] + ch[2],
            ch[1] + ch[2] + ch[0]
        ]
    else:
        anagrammes = [
            ch[2] + ch[0] + ch[1],
            ch[2] + ch[1] + ch[0]
        ]
    return anagrammes


def est_dans_tableau(tab, ch):
    return ch in tab


def remplir_tab_anagrammes(tab, ch):
    for anagram in [anagramme_pos(ch, i) for i in range(len(ch))]:
        tab.append(anagram)

def test():
    print("Anagram generation : ", end="")
    ch = "abc"
    anagrams = [['abc', 'acb'], ['bac', 'bca'], ['cab', 'cba']]
    tab = []
    remplir_tab_anagrammes(tab, ch)

    if tab == anagrams:
        cprint("PASS", 'blue')
    else:
        cprint("FAIL", 'red')

if __name__ == "__main__":
    ch = ""
    tab = []
    while len(ch) != 3:
        ch = input("Entrez un mot de 3 lettres : >>> ")
    remplir_tab_anagrammes(tab, ch)
    print("Anagrams of", ch, ":", tab)
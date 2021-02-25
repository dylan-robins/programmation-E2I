#!/usr/bin/env python
# -*- coding: utf-8 -*-
from color_print import cprint

def compter_mots(ch):
    words = ch.split()
    return len(words)

def retourner_mot(ch, pos):
    words = ch.split()
    return words[pos], sum(len(word) for word in words[:pos])

def chercher_mot(ch, nb_tab, mot):
    for i, pair in enumerate(nb_tab):
        if pair["mot"] == mot:
            return i
    return -1

def test():
    print("Recherche de mots : ", end="")
    phrase = "je crois ce que je dis et je fais ce que je crois "
    occurences = [
        {'mot': 'je',    'occurences': 4},
        {'mot': 'crois', 'occurences': 2},
        {'mot': 'ce',    'occurences': 2},
        {'mot': 'que',   'occurences': 2},
        {'mot': 'dis',   'occurences': 1},
        {'mot': 'et',    'occurences': 1},
        {'mot': 'fais',  'occurences': 1}
    ]

    nb_mots = compter_mots(phrase)
    tab = []
    # pour chaque mot
    for i in range(nb_mots):
        # trouver sa 1e occurence dans la chaine
        ieme_mot, pos = retourner_mot(phrase, i)
        # trouver l'indice de ce mot dans notre dict
        idex = chercher_mot(phrase, tab, ieme_mot)
        if idex == -1:
            # 1e occurence du mot: le rajouter à la liste
            tab.append( {"mot": ieme_mot, "occurences": 1} )
        else:
            # incrémenter le compteur
            tab[idex]["occurences"] += 1
    
    if tab == occurences:
        cprint("PASS", 'blue')
    else:
        cprint("FAIL", 'red')

if __name__ == "__main__":
    phrase = input("Entrez une phrase:\n>>> ")
    nb_mots = compter_mots(phrase)
    tab = []
    # pour chaque mot
    for i in range(nb_mots):
        # trouver sa 1e occurence dans la chaine
        ieme_mot, pos = retourner_mot(phrase, i)
        # trouver l'indice de ce mot dans notre dict
        idex = chercher_mot(phrase, tab, ieme_mot)
        if idex == -1:
            # 1e occurence du mot: le rajouter à la liste
            tab.append( {"mot": ieme_mot, "occurences": 1} )
        else:
            # incrémenter le compteur
            tab[idex]["occurences"] += 1
    
    for word in tab:
        print(
            f"{word['mot']} : {word['occurences']}",
            "occurence" if word['occurences'] == 1 else "occurences"
        )


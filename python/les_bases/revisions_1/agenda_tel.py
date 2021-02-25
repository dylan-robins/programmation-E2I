#!/usr/bin/env python
# -*- coding: utf-8 -*-
from color_print import cprint

def saisir_numero(tel):
    tel["code"]= input("Code région (ex: +33) ?\n>>> ")
    tel["num"] = input("Numéro (ex: 412345678) ?\n>>> ")

def saisir_liste_telephones():
    tels = []
    for _ in range(3):
        tels.append({})
        saisir_numero(tels[-1])
    return tels

def saisir_personne():
    p = {}
    p["nom"] = input("Nom de la personne ?\n>>> ")
    p["nums"] = saisir_liste_telephones()
    p["nationalite"] = input(f"Nationalité de {p['nom']} ?\n>>> ")
    return p

def afficher_personne(personne):
    print(f"{personne['nom']} ({personne['nationalite']}) :")
    for tel in personne['nums']:
        print(f"    ", tel['code'], tel['num'], sep='')

def afficher_nationalite(agenda):
    nat = input("Nationalité à rechercher dans l'agenda ?\n>>> ")
    for personne in agenda:
        if personne["nationalite"] == nat:
            afficher_personne(personne)

def chercher_num(agenda):
    num = {}
    saisir_numero(num)
    for personne in agenda:
        if num in personne["nums"]:
            afficher_personne(personne)


if __name__ == "__main__":
    print("Création agenda téléphonique :")
    agenda = []
    N = int(input("Nombre de personnes à rajouter à l'agenda : >>> "))
    for _ in range(N):
        agenda.append(saisir_personne())

    for entry in agenda:
        print(entry)

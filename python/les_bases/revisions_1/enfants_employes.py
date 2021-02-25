#!/usr/bin/env python
# -*- coding: utf-8 -*-
from color_print import cprint

def saisir_date():
    date = {}
    date["jour"] = int(input("Jour ? >>> "))
    date["mois"] = int(input("Mois ? >>> "))
    date["annee"] = int(input("Année ? >>> "))
    return date

def saisir_enfant():
    enfant = {}
    enfant["prenom"] = input("Prénom de l'enfant ? >>> ")
    enfant["anniv"] = saisir_date()
    return enfant

def saisir_employe():
    employe = {}
    employe["nom"] = input("Nom de l'employé ? >>> ")
    employe["prenom"] = input("Prénom de l'employé ? >>> ")
    employe["nb_enfants"] = int(input("Nombre d'enfants ? >>> "))
    employe["enfants"] = []
    for child in range(employe["nb_enfants"]):
        employe["enfants"].append(saisir_enfant())
    return employe

def saisir_entreprise():
    entreprise = {}
    entreprise["nb_employes"] = int(input("Nombre d'employes ? >>> "))
    entreprise["employes"] = []
    for employe in range(entreprise["nb_employes"]):
        entreprise["employes"].append(saisir_employe())
    return entreprise

def nombre_enfants_entreprise(entreprise):
    return sum(employe["nb_enfants"] for employe in entreprise["employes"])

def compare_dates(d1, d2):
    if d1["annee"] < d2["annee"]:
        return -1
    elif d1["annee"] == d2["annee"] and d1["mois"] < d2["mois"]:
        return -1
    elif d1["annee"] == d2["annee"] and d1["mois"] == d2["mois"] and d1["jour"] < d2["jour"]:
        return -1
    elif d1["annee"] == d2["annee"] and d1["mois"] == d2["mois"] and d1["jour"] == d2["jour"]:
        return 0
    else:
        return 1

def plus_jeune_enfant(entreprise):
    # Initialiser le plus jeune au 1e enfant du 1e employé
    plus_jeune = entreprise["employes"][0]["enfants"][0]

    # comparer un par un les enfants de tous les employés
    for employe in entreprise["employes"]:
        for child in employe["enfants"]:
            if compare_dates(plus_jeune["anniv"], child["anniv"]) < 0:
                plus_jeune = child
    return plus_jeune

def fdate(date):
    return f"{date['jour']}/{date['mois']}/{date['annee']}"


if __name__ == "__main__":
    entreprise = saisir_entreprise()
    print("")
    print("Enfants :")
    for employe in entreprise["employes"]:
        for child in employe["enfants"]:
            print(f"{child['prenom']} ({fdate(child['anniv'])})")

    child = plus_jeune_enfant(entreprise)
    print(f"Enfant le plus jeune: {child['prenom']}, ({fdate(child['anniv'])})")
    
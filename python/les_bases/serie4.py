entr = {}
entr["nb_employes"] = int(input("Entrez le nombre d'employés : "))

entr["tab_emp"] = [None] * entr["nb_employes"]
for i in range(entr["nb_employes"]):
    print("\nSaisir les informations de l'employe {:d}".format(i+1))
    e = {}
    e["nom"] = input("Entrez son nom : ")
    e["prenom"] = input("Entrez son prénom : ")
    e["nb_enfants"] = input("Entrez son nombre d'enfants : ")
    entr["tab_emp"][i] = e

if __name__ == "__main__":
    print("Employés de l'entreprise:")
    total_kids = 0
    for i in range(entr["nb_employes"]):
        employe = entr["tab_emp"][i]
        print(f"L'employé {employe['prenom']} {employe['nom']} a {employe['nb_enfants']} enfants.")
        total_kids += employe['nb_enfants']

    print(f"Au total, les employés ont {total_kids} enfants.")
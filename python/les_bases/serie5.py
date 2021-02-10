##############################################################################
# Question 1
##############################################################################
def produit_val(val):
    val = val * val
    print(type(val))

def question1():
    tab = [2, 3, 6, 8, 10]
    print("Tab initial =", tab)
    produit_val(tab[1])
    print("Tab final =", tab)
    # rien ne change car int immutable

##############################################################################
# Question 2
##############################################################################

def moyenne_3_notes():
    n1 = float(input("Note 1 ? >>> "))
    n2 = float(input("Note 2 ? >>> "))
    n3 = float(input("Note 3 ? >>> "))
    return (n1 + n2 + n3) / 3

def moyenne_max_notes():
    nmax = 0
    somme = 0
    for i in range(3):
        note = float(input("Note {} ? >>> ".format(i)))
        if (note > nmax):
            nmax = note
        somme += note
    return somme / 3, nmax

def moyenne_notes():
    somme = 0
    for i in range(3):
        note = float(input("Note {} ? >>> ".format(i)))
        if not (0 < note < 20):
            return -1 
        somme += note
    return somme / 3

def question2():
    print("Moyenne: ", moyenne_3_notes())

    moy, nmax = moyenne_max_notes()
    print("Moyenne:", moy, "Maximum:", nmax)
    
    print("Moyenne: ", moyenne_notes())

##############################################################################
# Question 3
##############################################################################

def remplir_enseignement(enseignement):
    filiere = input("Nom de la filière? >>> ")
    respo = input("Nom du responsable? >>> ")
    enseignement["filiere"] = filiere
    enseignement["responsable"] = respo

def aff_par_filiere(enseignements):
    for ens in sorted(enseignements, key=lambda ens: ens["filiere"]):
        print(f"{ens['code']}: filiere {ens['filiere']} - reponsable{ens['responsable']}")

def aff_par_respo(enseignements):
    for ens in sorted(enseignements, key=lambda ens: ens["responsable"]):
        print(f"{ens['code']}: filiere {ens['filiere']} - reponsable {ens['responsable']}")


def question3():
    enseignements = []
    while len(enseignements) < 50:
        ens = input("Enseignement à remplir ? (Q/q pour quitter) >>> ")
        if ens in ["Q", "q"]:
            break
        enseignements.append( {"code": ens} )
        remplir_enseignement(enseignements[-1])

    aff_par_filiere(enseignements)
    aff_par_respo(enseignements)

if __name__ == "__main__":
    question1()
    question2()
    question3()
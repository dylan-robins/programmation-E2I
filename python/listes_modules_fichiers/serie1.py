#!/usr/bin/env python
# -*- coding: utf-8 -*-

###############################################################################
# EXO 1
###############################################################################
def exercice1(catalogue):
    matières_théoriques = [ue for ue in catalogue if ue[3] == 'T']
    print(
        "nombre de matières théoriques présentes dans le catalogue:",
        len(matières_théoriques)
    )
    
###############################################################################
# EXO 2
###############################################################################
def exercice2(promo):
    noms = [etu[1] for etu in promo]
    print(
        "Liste des noms d'étudiants dans l'ordre alphabétique:",
        " ".join(noms.sort())
    )
    
###############################################################################
# EXO 3
###############################################################################
def DictionnaireApogee(catalogue):
    """cree et retourne un dictionnaire qui associe un code apogee à l'intitule de l'UF"""
    mapping = {}
    for uf in catalogue:
        mapping[uf[0]] = uf[1]
    return mapping
    
def IntituleListeCodeApogee(catalogue, lstcode):
    """affiche les intitules des matieres associés à la liste des codes apogee lstcode"""
    map = DictionnaireApogee(catalogue)
    for code in lstcode:
        print(f"{code}: {map[code]}")

def exercice3(promo, catalogue):
    for etu in promo:
        print("Matières suivies par", etu[1])
        IntituleListeCodeApogee(catalogue, etu[3])

if __name__ == "__main__":
    catalogue=[
        ['KAEI7M01', 'Anglais 3', 'P', 30, 2], 
        ['KAEI7M02', 'Communication 2', 'P', 15, 1], 
        ['KAEI7M03', 'Mathematiques 3', 'T', 15, 1], 
        ['KAEI7M04', 'Programmation 3', 'P', 30, 2], 
        ['KAEI7M05', 'Informatique industrielle 1', 'P', 30, 2], 
        ['KAEI7M06', 'Electronique 3', 'P', 60, 4], 
        ['KAEI7M07', 'Traitement numerique des signaux 1', 'T', 30, 2], 
        ['KAEI8M01', 'Anglais 4', 'P', 30, 2], 
        ['KAEI8M02', 'Gestion de projets', 'P', 30, 2], 
        ['KAEI8M03', 'Economie', 'T', 15, 1], 
        ['KAEI8M04', 'Analyse numerique', 'T', 30, 2], 
        ['KAEI8M05', 'UNIX 1', 'P', 15, 1], 
        ['KAEI8M06', 'Informatique industrielle 2', 'P', 30, 2], 
        ['KAEI8M07', "Conversion d'energie 2", 'T', 30, 2], 
        ['KAEI8M08', 'Traitement numerique des signaux 2', 'T', 30, 2], 
        ['KAEI8M09', 'Regulation numerique', 'T', 45, 3]
    ]

    promotion= [
        [190128003, 'Thomas', 7, ['KAEI7M01', 'KAEI7M02', 'KAEI7M03', 'KAEI7M04', 'KAEI7M05', 'KAEI7M06', 'KAEI7M07']], 
        [190128004, 'Petit', 9, ['KAEI8M01', 'KAEI8M02', 'KAEI8M03', 'KAEI8M04', 'KAEI8M05', 'KAEI8M06', 'KAEI8M07', 'KAEI8M08', 'KAEI8M09']], 
        [190128009, 'Aguilar', 7, ['KAEI7M01', 'KAEI7M02', 'KAEI7M03', 'KAEI7M04', 'KAEI7M05', 'KAEI7M06', 'KAEI7M07']], 
        [190128010, 'Alvar', 9, ['KAEI8M01', 'KAEI8M02', 'KAEI8M03', 'KAEI8M04', 'KAEI8M05', 'KAEI8M06', 'KAEI8M07', 'KAEI8M08', 'KAEI8M09']], 
        [190128015, 'Santos', 7, ['KAEI7M01', 'KAEI7M02', 'KAEI7M03', 'KAEI7M04', 'KAEI7M05', 'KAEI7M06', 'KAEI7M07']], 
        [190128016, 'Pereira', 9, ['KAEI8M01', 'KAEI8M02', 'KAEI8M03', 'KAEI8M04', 'KAEI8M05', 'KAEI8M06', 'KAEI8M07', 'KAEI8M08', 'KAEI8M09']], 
        [190128021, 'Peeters', 7, ['KAEI7M01', 'KAEI7M02', 'KAEI7M03', 'KAEI7M04', 'KAEI7M05', 'KAEI7M06', 'KAEI7M07']], 
        [190128022, 'Jacobs', 9, ['KAEI8M01', 'KAEI8M02', 'KAEI8M03', 'KAEI8M04', 'KAEI8M05', 'KAEI8M06', 'KAEI8M07', 'KAEI8M08', 'KAEI8M09']]
    ]
    
    exercice1(catalogue)
    exercice2(promotion)
    exercice3(promotion, catalogue)

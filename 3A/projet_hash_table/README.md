# Projet table de hachage

Sébastien CACHARD - Chloé NOUGIER - Dylan ROBINS  
E2I3

## Compilation

Le Makefile fourni permet de compiler toutes les parties nécessaires.

Targets fournis:  
+ all (par défaut) : crée les sous-dossiers `./bin` et `./obj` puis compile le
                     programme dans `./bin`  
+ clean : supprime les dossiers `./bin` et `./obj` ainsi que leur contenu

## Lancement du programme

Lorsque vous lancez le programme (`./bin/dico`), il lancera automatiquement les
tests. Pour faciliter la lecture des résultats, les affichages "PASS" et "FAIL"
sont colorisés en bleu et en rouge respectivement.

Voici un aperçu des résultats attendus:

```
$ ./bin/dico 
*** Dictionnaire : 1ere partie ***
*** Construction d'une liste chainee simple ***

Dictionnaire (liste) charge : 642242 mots trouves
Nombre de noeuds de la liste (iteratif) : 642242
        > PASS
<chien> est dans la liste : Oui
        > PASS
<microcontrolleur> est dans la liste : Non
Ajout du mot <microcontrolleur>
        > PASS
Erreur: "t" inconnu [1,94]
Erreur: "aucuns" inconnu [9,23]
Erreur: "sida" inconnu [36,20]
Erreur: "t" inconnu [72,9]
Erreur: "Étais" inconnu [90,41]
file checked in 4441 ms
        > PASS


*** Dictionnaire : 2ieme partie ***
*** Construction d'une table de hachage ***

Longueur de la liste la plus courte : 1168
Longueur de la liste la plus longue : 1466
Moyenne des longueurs des listes : 1280
        > PASS
<chien> est dans la table : Oui
        > PASS
Erreur: "t" inconnu [1,94]
Erreur: "aucuns" inconnu [9,23]
Erreur: "sida" inconnu [36,20]
Erreur: "t" inconnu [72,9]
Erreur: "Étais" inconnu [90,41]
file checked in 151 ms
        > PASS
```
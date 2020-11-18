#include "salaries.h"

#include <cstring>
#include <iostream>

using namespace std;

// Définitions classe salarie

salarie::salarie(char *nom, int bureau) {
    _nom = new char[strlen(nom) + 1];
    strcpy(_nom, nom);
    set_bureau(bureau);
    _nb_salaries++;
}
salarie::~salarie() {
    _nb_salaries--;
    delete[] _nom;
}

void salarie::afficher() {
    cout << "nom : " << _nom << endl
         << "bureau : " << _bureau << endl
         << "tel : " << get_telephone() << endl;
}

void salarie::set_bureau(int bureau) {
    _bureau = bureau;
}

char *salarie::get_telephone() {
    static char *telephone[] = {"001", "002", "003", "004", "005", "006"};
    int nb_tels = sizeof(telephone) / sizeof(*telephone);  // 6
    if (_bureau > 0 && _bureau <= nb_tels)
        return telephone[_bureau - 1];
    else
        return "000";
}

unsigned long salarie::get_nb_salaries() {
    return _nb_salaries;
}

// Définitions classe employe

employe::employe(char *nom, int bureau,
                 float taux_horaire, float nb_heures) : salarie(nom, bureau) {
    set_taux(taux_horaire);
    set_heures(nb_heures);
    _nb_employes++;
}

employe::~employe() {
    _nb_employes--;
}

void employe::afficher() {
    salarie::afficher();
    cout << "taux_h : " << _taux_horaire << endl
         << "heures work : " << _nb_heures << endl;
}

void employe::set_taux(float taux_horaire) {
    _taux_horaire = taux_horaire;
}


void employe::set_heures(float nb_heures) {
    _nb_heures = nb_heures;
}

float employe::calcul_salaire() {
    return _taux_horaire * _nb_heures;
}

unsigned long employe::get_nb_employes() {
    return _nb_employes;
}

// Définitions classe commercial

commercial::commercial(char *nom, float chiffre_affaire, int bureau, float taux_horaire,
               float nb_heures, float pourcentage) : employe(nom, bureau, taux_horaire, nb_heures) {
    set_pourcentage(pourcentage);
    set_chiffre_affaire(chiffre_affaire);
    _nb_commerciaux++;
}

commercial::~commercial() {
    _nb_commerciaux--;
}

void commercial::afficher() {
    employe::afficher();
    cout << "pourcentage des ventes : " << _pourcentage << endl
         << "chiffre affaire : " << _chiffre_affaire << endl;
}

void commercial::set_pourcentage(float pourcentage) {
    _pourcentage = pourcentage;
}

void commercial::set_chiffre_affaire(float chiffre_affaire) {
    _chiffre_affaire = chiffre_affaire;
}

float commercial::calcul_salaire() {
    return employe::calcul_salaire() + (_pourcentage * _chiffre_affaire);
}

unsigned long commercial::get_nb_commerciaux() {
    return _nb_commerciaux;
}

// Définitions classe directeur

directeur::directeur(char *nom, int bureau, float fixe,
                     float prime, int nb_employes)
    : salarie(nom, bureau) {
    set_fixe(fixe);
    set_prime(prime);
    set_nb_employe(_nb_employe);
    _nb_directeurs++;
}

directeur::~directeur() {
    _nb_directeurs--;
}

void directeur::afficher() {
    salarie::afficher();
    cout << "salaire fixe : " << _fixe << endl
         << "la prime : " << _prime << endl
         << "nombre de salarié : " << _nb_employe << endl;
}

void directeur::set_fixe(float fixe) {
    _fixe = fixe;
}

void directeur::set_prime(float prime) {
    _prime = prime;
}

void directeur::set_nb_employe(int nb_employe) {
    _nb_employe = nb_employe;
}

float directeur::calcul_salaire() {
    return _fixe + _prime;
}

unsigned long directeur::get_nb_directeurs() {
    return _nb_directeurs;
}
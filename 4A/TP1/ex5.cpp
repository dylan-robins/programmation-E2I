#include <iostream>
#include <random>
#include <cstring>

using namespace std;

long somme(int *tab, const int len) {
    long s = 0;
    for (int i = 0; i < len; i++) {
        s += tab[i];
    }
    return s;
}

int main(void) {
    const int capacite = 100;
    int taille = 10;
    int tab[capacite];


    // init rng
    random_device rd;
    uniform_int_distribution<int> dist(0, 100);

    // Partie 1
    cout << "###########################" << endl;
    cout << "Partie 1" << endl;
    cout << "###########################" << endl;
    
    // populer tab avec 0 entiers au pif
    cout << "Liste: ";
    for (int i = 0; i < taille; i++) {
        tab[i] = dist(rd);
        cout << tab[i] << " ";
    }
    cout << endl;

    cout << "Somme: " << somme(tab, taille) << endl;

    for (int i = 0; i < taille; i++) {
        cout << "Entrez un nombre" << endl << ">>> ";
        cin >> tab[i];
    }

    cout << "Tableau : ";
    for (int i = 0; i < taille; i++) {
        cout << tab[i] << " ";
    }
    cout << endl;
    cout << "Somme: " << somme(tab, taille) << endl;


    // Partie 2
    cout << "###########################" << endl;
    cout << "Partie 2" << endl;
    cout << "###########################" << endl;
    taille = 0;
    char buffer[512] = "";
    // Lire jusqu'à 100 numéros
    while (taille <= capacite) {
        cout << "Entrez un nombre ou (q/Q) pour terminer : ";
        cin >> buffer;
        if (strcmp("q", buffer) == 0 || strcmp("Q", buffer) == 0) {
            break;
        }
        tab[taille] = atoi(buffer);
        taille++;
    }
    cout << "Tableau : ";
    for (int i = 0; i < taille; i++) {
        cout << tab[i] << " ";
    }
    cout << endl;
    cout << "Somme: " << somme(tab, taille) << endl;

    return 0;
}
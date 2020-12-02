#include "liste_points.h"

#include <iostream>

using namespace std;

void ListePoints::afficher() {
    cout << "[" << *(Point *)premier();
    while (!fini()) {
        cout << ", " << *(Point *)prochain();
    }
    cout << "]" << endl;
}
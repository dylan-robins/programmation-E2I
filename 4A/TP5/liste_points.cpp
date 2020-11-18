#include "liste_points.h"

#include <iostream>

using namespace std;

void ListePoints::afficher() {
    cout << "[" << premier();
    while (!fini()) {
        cout << ", " << prochain();
    }
    cout << "]" << endl;
}
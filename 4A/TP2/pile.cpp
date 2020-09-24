#include "pile.h"

#include <iostream>

using namespace std;

void Pile::empiler(int element) {
    if (_etat != plein)
        _table[_nb_elem++] = element;
    else
        cout << "pile pleine" << endl;
    if (_nb_elem >= _max)
        _etat = plein;
    else
        _etat = ok;
}

int Pile::depiler() {
    int element = 0;
    if (_etat != vide)
        element = _table[--_nb_elem];
    else
        cout << "pile vide" << endl;
    if (_nb_elem <= 0)
        _etat = vide;
    else
        _etat = ok;
    return element;
}

void Pile::afficher() {
    for (int i = _nb_elem - 1; i >= 0; i--) cout << _table[i] << endl;
}

inline int Pile::nb_elements() { return _nb_elem; }
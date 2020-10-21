#include "vecteur3d.h"

#include <iostream>
using namespace std;

Vecteur3d::Vecteur3d() {
    _data[0] = 0;
    _data[1] = 0;
    _data[2] = 0; 
}

Vecteur3d::Vecteur3d(const double x, const double y, const double z) {
    _data[0] = x;
    _data[1] = y;
    _data[2] = z;
}

double Vecteur3d::get(const unsigned long i) {
    if (i > 2) {
        cerr << "Error: invalid field number " << i << " for vecteur3d!" << endl;
        exit(EXIT_FAILURE);
    }
    return _data[i];
}

double Vecteur3d::get(const field_t champs) {
    return _data[(unsigned long)champs];
}

void Vecteur3d::set(const unsigned long i, const double data) {
    if (i > 2) {
        cerr << "Error: invalid field number " << i << " for vecteur3d!" << endl;
        exit(EXIT_FAILURE);
    }
    _data[i] = data;
}
void Vecteur3d::set(const field_t champs, const double data) {
    _data[(unsigned long)champs] = data;
}

void Vecteur3d::display() {
    cout << "{";
    for (size_t i = 0; i < 3; i++) {
        cout << _data[i] << " ";
    }
    cout << "}" << endl;
}
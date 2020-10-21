#include "matrice.h"

#include <iostream>
#include <iomanip>
using namespace std;


Matrice::Matrice() {
    // on alloue les données sur le heap pour pouvoir facilement faire une
    // classe generique plus tard !

    // allouer tableau de lignes
    _data = new double*[_nb_rows];
    for (unsigned long row = 0; row < _nb_rows; row++) {
        // allouer chaque ligne
        _data[row] = new double[_nb_cols];

        for (unsigned long col = 0; col < _nb_cols; col++) {
            cout << "Coefficient " << row << "x" << col << " de la matrice?" << endl << ">>> ";
            cin >> _data[row][col];
        }
    }
}

Matrice::Matrice(const double tab[3][3]) {
    // on alloue les données sur le heap pour pouvoir facilement faire une
    // classe generique plus tard !

    // allouer tableau de lignes
    _data = new double*[_nb_rows];
    for (unsigned long row = 0; row < _nb_rows; row++) {
        // allouer chaque ligne
        _data[row] = new double[_nb_cols];

        for (unsigned long col = 0; col < _nb_cols; col++) {
            _data[row][col] = tab[row][col];
        }
    }
}

Matrice::~Matrice() {
    for (unsigned long row = 0; row < _nb_rows; row++) {
        delete _data[row];
    }
    delete _data;
}

double Matrice::get(const unsigned long row, const unsigned long col) {
    if (row < 0 || row >= _nb_rows) {
        cerr << "Error: row number out of bounds " << row << endl;
        exit(EXIT_FAILURE);
    }
    if (col < 0 || col >= _nb_cols) {
        cerr << "Error: column number out of bounds " << col << endl;
        exit(EXIT_FAILURE);
    }
    return _data[row][col];
}

void Matrice::set(const unsigned long row, const unsigned long col, const double data) {
    if (row < 0 || row >= _nb_rows) {
        cerr << "Error: row number out of bounds " << row << endl;
        exit(EXIT_FAILURE);
    }
    if (col < 0 || col >= _nb_cols) {
        cerr << "Error: column number out of bounds " << col << endl;
        exit(EXIT_FAILURE);
    }
    _data[row][col] = data;
}

void Matrice::display() {
    for (unsigned long row = 0; row < _nb_rows; row++) {
        for (unsigned long col = 0; col < _nb_cols; col++) {
            cout << setw(5) << _data[row][col];
        }
        cout << endl;
    }
}

Vecteur3d Matrice::produit_vec_mat(Vecteur3d& v) {
    // On considère que le vecteur v et res sont des vecteurs ligne, sinon
    // les dimensions ne collent pas 
    Vecteur3d res;
    for (unsigned long col = 0; col < _nb_cols; col++) {
        for (unsigned long row = 0; row < _nb_rows; row++) {
            res.set(
                col,
                res.get(col) + v.get(row) * get(row, col)
            );
        }
    }
    return res;
}

Vecteur3d Matrice::produit_mat_vec(Vecteur3d& v) {
    // On considère que v est un vecteur ligne et que res est un vecteur ligne,
    // sinon les dimensions ne collent pas 
    Vecteur3d res;
    for (unsigned long row = 0; row < _nb_rows; row++) {
        for (unsigned long col = 0; col < _nb_cols; col++) {
            res.set(
                row,
                res.get(row) + v.get(col) * get(row, col)
            );
        }
    }
    return res;
}
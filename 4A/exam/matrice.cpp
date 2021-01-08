#include "matrice.h"

#include <iomanip>
#include <iostream>

#include "complexe.h"

// Créé une matrice nulle de taille n*n (default: 3)
MatriceComplex::MatriceComplex(const unsigned int n) : _size(n) {
    // allouer lignes
    _m = new Complexe *[_size];
    // allouer colonnes
    for (int i = 0; i < _size; i++) {
        _m[i] = new Complexe[_size];
    }
}

// Créé une matrice de taille n*n (default: 3) et l'initialise avec les valeurs
// du tableau t
MatriceComplex::MatriceComplex(Complexe **t, const unsigned int n) : _size(n) {
    // allouer lignes
    _m = new Complexe *[_size];
    // allouer colonnes
    for (int i = 0; i < _size; i++) {
        _m[i] = new Complexe[_size];
    }

    for (int y = 0; y < _size; y++) {
        for (int x = 0; x < _size; x++) {
            _m[y][x] = t[y][x];
        }
    }
}

// Créé une matrice identique à la matrice m
MatriceComplex::MatriceComplex(const MatriceComplex &m) : _size(m._size) {
    // allouer lignes
    _m = new Complexe *[_size];
    // allouer colonnes
    for (int i = 0; i < _size; i++) {
        _m[i] = new Complexe[_size];
    }

    for (int y = 0; y < _size; y++) {
        for (int x = 0; x < _size; x++) {
            _m[y][x] = m(x, y);
        }
    }
}

// Libère la mémoire occupée par la matrice
MatriceComplex::~MatriceComplex() {
    // détruire les colonnes de chaque ligne
    for (int i = 0; i < _size; i++) {
        delete _m[i];
    }
    // détruire le tableau de lignes
    delete _m;
}

// Accède à l'élément d'indice row,col de la matrice
Complexe &MatriceComplex::operator()(const unsigned int row, const unsigned int col) {
    return _m[col][row];
}
// Accède à l'élément d'indice row,col de la matrice
Complexe MatriceComplex::operator()(const unsigned int row, const unsigned int col) const {
    return _m[col][row];
}

// insère la matrice dans un flux (default: std::cout)
std::ostream &operator<<(std::ostream &os, const MatriceComplex &m) {
    for (int y = 0; y < m._size; y++) {
        for (int x = 0; x < m._size; x++) {
            // afficher coeff
            os << std::setw(5) << m(x, y);

            // afficher séparateur
            if (x < m._size - 1)
                os << ",";
        }
        os << std::endl;
    }
    return os;
}
// extrait les coefficients de la matrice depuis un flux (default: std::cin)
std::istream &operator>>(std::istream &is, MatriceComplex &m) {
    for (int y = 0; y < m._size; y++) {
        for (int x = 0; x < m._size; x++) {
            Complexe &coeff = m(x, y);
            is >> coeff;
        }
    }
    return is;
}

// addition de deux matrices
MatriceComplex operator+(const MatriceComplex &m1, const MatriceComplex &m2) {
    // vérification de cohérence
    if (m1._size != m2._size) {
        std::cerr << "Erreur: Dimensions incompatibles pour l'addition de matrices."
                  << m1._size << " != " << m2._size << std::endl;
        exit(1); // erreur fatale
    }

    MatriceComplex m3 = m1; // copie de m1

    // rajouter à m3 les coefficients de m2
    for (int y = 0; y < m3._size; y++) {
        for (int x = 0; x < m3._size; x++) {
            m3(x, y) += m2(x, y);
        }
    }
    return m3;
}
// multiplication de deux matrices
MatriceComplex operator*(const MatriceComplex &m1, const MatriceComplex &m2) {
    // vérification de cohérence
    if (m1._size != m2._size) {
        std::cerr << "Erreur: Dimensions incompatibles pour la multiplication de matrices."
                  << m1._size << " != " << m2._size << std::endl;
        exit(2); // erreur fatale
    }

    MatriceComplex result(m1._size);

    // rajouter à result les coefficients de m2
    for (int y = 0; y < result._size; y++) {
        for (int x = 0; x < result._size; x++) {
            for (int n = 0; n < result._size; n++) {
                result(x, y) += m1(n, y) * m2(x, n);
            }
        }
    }
    return result;
}
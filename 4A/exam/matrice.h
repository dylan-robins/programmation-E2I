#ifndef __MATRICE_H__
#define __MATRICE_H__

#include "complexe.h"

#include <iostream>

class MatriceComplex {
  public:
    // Créé une matrice nulle de taille n*n (default: 3)
    MatriceComplex(const unsigned int n = 3);
    // Créé une matrice de taille n*n (default: 3) et l'initialise avec les valeurs
    MatriceComplex(Complexe **t, const unsigned int n);
    // Créé une matrice identique à la matrice m
    MatriceComplex(const MatriceComplex &m);
    // Libère la mémoire occupée par la matrice
    ~MatriceComplex();

    // Accède à l'élément d'indice row,col de la matrice
    Complexe &operator()(const unsigned int row, const unsigned int col);
    // Accède à l'élément d'indice row,col de la matrice
    Complexe operator()(const unsigned int row, const unsigned int col) const;

  private:
    unsigned int _size;
    Complexe **_m;

    // insère la matrice dans un flux (default: std::cout)
    friend std::ostream &operator<<(std::ostream &os, const MatriceComplex &m);
    // extrait les coefficients de la matrice depuis un flux (default: std::cin)
    friend std::istream &operator>>(std::istream &is, MatriceComplex &m);

    // On définit les opérateurs symétriques en friend afin de bénéficier d'une meilleure gestion des conversions automatiques
    // En accord avec la spec isocpp https://github.com/isocpp/CppCoreGuidelines/blob/036324/CppCoreGuidelines.md#c161-use-nonmember-functions-for-symmetric-operators

    // addition de deux matrices
    friend MatriceComplex operator+(const MatriceComplex &m1, const MatriceComplex &m2);
    // multiplication de deux matrices
    friend MatriceComplex operator*(const MatriceComplex &m1, const MatriceComplex &m2);
};

#endif
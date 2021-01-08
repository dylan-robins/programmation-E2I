// Author:    Dylan Robins
// Created:   08/01/2021

#include "matrice.h"
#include <iostream>

int main() {
    MatriceComplex m;
    MatriceComplex n(3);
    Complexe z;

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            n(x, y) = 3 * y + x;
        }
    }

    std::cin >> m;

    std::cout
        << "Matrice m :" << std::endl
        << m << std::endl
        << "Matrice n :" << std::endl
        << n << std::endl
        << "m + n :" << std::endl
        << m + n << std::endl
        << "m * n :" << std::endl
        << m * n << std::endl;
    return 0;
}

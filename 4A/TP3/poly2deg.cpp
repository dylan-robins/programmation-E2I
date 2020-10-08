#include "poly2deg.h"

#include <cmath>
#include <iostream>

#include "complexe.h"

using namespace std;

void Poly2Deg::afficher() {
    cout << _a << "x^2 + " << _b << "x + " << _c << endl;
}

Complexe Poly2Deg::solution() {
    int d = delta();
    if (d == 0) {
        return Complexe(-_b / (2.0 * _a), 0);
    } else if (d > 0) {
        return Complexe( (sqrt(d) - (double)_b) / (2.0 * _a), 0);
    } else {
        return Complexe(-_b / (2.0 * _a), sqrt(-d) / (2.0 * _a));
    }
}

int Poly2Deg::delta() {
    return _b * _b - 4 * _a * _c;
}
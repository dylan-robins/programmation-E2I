#include "vec3d.h"

#include <iostream>

using namespace std;

#define EX1QE

// EXERCICE 1
// Question 1.a
Vecteur3d::Vecteur3d(void) {
    _x = 0;
    _y = 0;
    _z = 0;
}
#ifdef EX1QA
Vecteur3d::Vecteur3d(const double x, const double y, const double z) {
    _x = x;
    _y = y;
    _z = z;
}
#endif

void Vecteur3d::afficher() const {
    cout << '{' << _x << ',' << _y << ',' << _z << '}' << endl;
}

// Question 1.b
#ifdef EX1QB
Vecteur3d::Vecteur3d(const double x = 0, const double y = 0, const double z = 0) {
    _x = x;
    _y = y;
    _z = z;
}
#endif

// Question 1.e
#ifdef EX1QE
Vecteur3d::Vecteur3d(const double x, const double y, const double z) : _x(x), _y(y), _z(z) {}
#endif

// Question 2
Vecteur3d::Vecteur3d(const Vecteur3d &a_copier) : _x(a_copier._x), _y(a_copier._y), _z(a_copier._z) {}
#ifndef __POLY2DEG_H__
#define __POLY2DEG_H__

#include "complexe.h"

class Poly2Deg {
private:
    int _a, _b, _c;

public:
    Poly2Deg(int a = 0, int b = 0, int c = 0) : _a(a), _b(b), _c(c){};
    void afficher();
    Complexe solution();
    int delta();
};

#endif
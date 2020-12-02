#include "points.h"

#include <iostream>
using namespace std;

#define EX1

int main() {
#ifdef EX1
    Colour red(col_t::red);
    Colour blue(col_t::blue);
    Colour yellow(col_t::yellow);
    Colour reset(col_t::reset);

    Pointcol x(5, 0, red);
    x.affiche();

    Pointcol y(1, 1, blue);
    y.affiche();
    
    Pointcol z(2.5, 3.1415, yellow);
    z.affiche();
#endif
    return 0;
}
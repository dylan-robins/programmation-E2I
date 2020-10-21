#ifndef __MATRICE_H__
#define __MATRICE_H__

#include "vecteur3d.h"

class Matrice {
private:
    double **_data;
    const unsigned long _nb_rows = 3; // definies en tant que membre pour
    const unsigned long _nb_cols = 3; // pouvoir facilement faire une classe
                                      // generique plus tard

public:
    Matrice();
    Matrice(const double tab[3][3]);
    ~Matrice();
    double get(const unsigned long row, const unsigned long col);
    void set(const unsigned long row, const unsigned long col, const double data);
    void display();
    Vecteur3d produit_vec_mat(Vecteur3d& v);
    Vecteur3d produit_mat_vec(Vecteur3d& v);
};

#endif
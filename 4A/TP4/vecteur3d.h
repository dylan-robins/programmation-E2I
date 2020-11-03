#ifndef __VECTEUR3D_H__
#define __VECTEUR3D_H__

#include <iostream>

class Vecteur3d
{
private:
    friend bool operator==(const Vecteur3d& v1, const Vecteur3d& v2);
    friend bool operator!=(const Vecteur3d& v1, const Vecteur3d& v2);
    friend Vecteur3d operator+(const Vecteur3d& v1, const Vecteur3d& v2);
    friend double operator*(const Vecteur3d& v1, const Vecteur3d& v2);
    // affiche les coords au format "{x,y,z}"
    friend std::ostream& operator<<(std::ostream& os, const Vecteur3d& v);
    // lit les 3 coordonnées séparées par du whitespace
    friend std::istream& operator>>(std::istream& is, Vecteur3d& v);

    static const unsigned long _dim = 3;
    double _data[_dim];

public:
    Vecteur3d();
    Vecteur3d(const double x, const double y, const double z);
    Vecteur3d(const Vecteur3d& v);
    double get(const unsigned long champs) const;
    void set(const unsigned long champs, double data);
    void display() const;
    unsigned long get_dim() const;
};

#endif
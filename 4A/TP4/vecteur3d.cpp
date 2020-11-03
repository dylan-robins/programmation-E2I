#include "vecteur3d.h"

#include <iostream>
using namespace std;

Vecteur3d::Vecteur3d() {
    for (size_t i = 0; i < get_dim(); i++) {
        set(i, 0);
    }
}

Vecteur3d::Vecteur3d(const double x, const double y, const double z) {
    _data[0] = x;
    _data[1] = y;
    _data[2] = z;
}

Vecteur3d::Vecteur3d(const Vecteur3d& v) {
    if (v.get_dim() != get_dim()) {
        cerr << "Incompatible_dimensions for vector copy!" << endl;
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < get_dim(); i++) {
        set(i, v.get(i));
    }
}

double Vecteur3d::get(const unsigned long i) const {
    if (i >= get_dim()) {
        cerr << "Error: invalid field number " << i << " for vecteur3d!" << endl;
        exit(EXIT_FAILURE);
    }
    return _data[i];
}

void Vecteur3d::set(const unsigned long i, const double data) {
    if (i >= get_dim()) {
        cerr << "Error: invalid field number " << i << " for vecteur3d!" << endl;
        exit(EXIT_FAILURE);
    }
    _data[i] = data;
}

unsigned long Vecteur3d::get_dim() const {
    return _dim;
}

void Vecteur3d::display() const {
    cout << "{";
    for (size_t i = 0; i < get_dim(); i++) {
        cout << get(i) << " ";
    }
    cout << "}" << endl;
}

bool operator==(const Vecteur3d& v1, const Vecteur3d& v2) {
    if (v1.get_dim() != v2.get_dim()) {
        return false;
    }
    for (unsigned long i = 0; i < v1.get_dim(); i++) {
        if (v1.get(i) != v2.get(i)) return false;
    }
    return true;
}

bool operator!=(const Vecteur3d& v1, const Vecteur3d& v2) {
    if (v1.get_dim() != v2.get_dim()) {
        return true;
    }
    for (unsigned long i = 0; i < v1.get_dim(); i++) {
        if (v1.get(i) != v2.get(i)) return true;
    }
    return false;
}

Vecteur3d operator+(const Vecteur3d& v1, const Vecteur3d& v2) {
    Vecteur3d new_vec;
    
    if (v1.get_dim() != v2.get_dim()) {
        cerr << "Incompatible_dimensions for vector addition!" << endl;
        exit(EXIT_FAILURE);
    }

    for (unsigned long i = 0; i < v1.get_dim(); i++) {
        new_vec.set(i, v1.get(i)+v2.get(i));
    }
    return new_vec;
}

double operator*(const Vecteur3d& v1, const Vecteur3d& v2) {
    double prod = 0;
    
    if (v1.get_dim() != v2.get_dim()) {
        cerr << "Incompatible_dimensions for vector product!" << endl;
        exit(EXIT_FAILURE);
    }

    for (unsigned long i = 0; i < v1.get_dim(); i++) {
        prod += v1.get(i)*v2.get(i);
    }

    return prod;
}

ostream& operator<<(ostream& os, const Vecteur3d& v) {
    os << "(" << v.get(0) << "," << v.get(1) <<  "," << v.get(2) << "}";
    return os;
}

istream& operator>>(istream& is, Vecteur3d& v) {
    is >> v._data[0] >> v._data[1] >> v._data[2] ;
    return is;
}
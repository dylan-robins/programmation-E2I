#include "points.h"

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

ostream& operator<<(ostream& os, const Colour& col) {
    os << "\033[" << col._col << "m";
    return os;
}

Point::Point(double abs = 0.0, double ord = 0.0) {
    _x = abs;
    _y = ord;
}
void Point::affiche() const {
    cout << this << endl;
}
void Point::deplace(double dx, double dy) {
    _x = _x + dx;
    _y = _y + dy;
}
ostream& operator<<(ostream& os, const Point& point) {
    os << "(" << point._x << "," << point._y << ")";
    return os;
}

Pointcol::Pointcol() : Point() {
    set_colour(col_t::black);
}

Pointcol::Pointcol(const double abs, const double ord) : Point(abs, ord) {
    set_colour(col_t::black);
}

Pointcol::Pointcol(const double abs, const double ord, const Colour col) : Point(abs, ord) {
    set_colour(col);
}

void Pointcol::set_colour(const Colour col) {
    _colour = col;
}

void Pointcol::affiche() const {
    Colour rst(col_t::reset);
    cout << _colour << (Point) *this << rst << endl;
}

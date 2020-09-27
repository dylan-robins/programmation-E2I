#include "point.h"

#include <cmath>
#include <iostream>

Point::Point() {
    _x = 0;
    _y = 0;
}
Point::Point(const double x, const double y) : _x(x), _y(y) {
    set_rad();
}

Point::Point(const Point &a_copier) {
    _x = a_copier._x;
    _y = a_copier._y;
    set_rad();
}

void Point::set_deg() {
    _mode = mode_t::deg;
}
void Point::set_rad() {
    _mode = mode_t::rad;
}

double Point::abscisse() { return _x; }

double Point::ordonnee() { return _y; }

double Point::rho() {
    return sqrt(pow(_x, 2) + pow(_y, 2));
}

double Point::teta() {
    return atan(_y / _x);
}

void Point::translate(const double x_off, const double y_off) {
    _x += x_off;
    _y += y_off;
}

void Point::rotation(const double angle) {
    double old_x = _x;
    double old_y = _y;
    _x = cos(angle) * old_x - sin(angle) * old_y;
    _y = sin(angle) * old_x + cos(angle) * old_y;
}
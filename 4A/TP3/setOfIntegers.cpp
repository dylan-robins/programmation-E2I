#include "setOfIntegers.h"

#include <iostream>

using namespace std;

Set_Of_Integer::Set_Of_Integer() : _capacity(50) {
    _tab = new int[50];
}

Set_Of_Integer::Set_Of_Integer(const size_t capacity) : _capacity(capacity) {
    _len = 0;
    _tab = new int[capacity];
}

Set_Of_Integer::~Set_Of_Integer() {
    delete _tab;
}

long Set_Of_Integer::indexOf(const int elem) {
    for (size_t i = 0; i < _len; i++) {
        if (elem == _tab[i]) {
            return i;
        }
    }
    return -1;
}

void Set_Of_Integer::add(const int elem) {
    if (indexOf(elem) == -1) {
        _tab[_len] = elem;
        _len++;
    }
}

void Set_Of_Integer::remove(const int elem) {
    long index = indexOf(elem);
    if (index != -1) {
        for (size_t i = index; i < _len-1; i++) {
            _tab[i] = _tab[i+1];
        }
        _len--;
    }
}

size_t Set_Of_Integer::cardinal() {
    return _len;
}

void Set_Of_Integer::display() {
    cout << "{";
    for (size_t i = 0; i < _len; i++) {
        cout << _tab[i] << " ";
    }
    cout << "}" << endl;
}
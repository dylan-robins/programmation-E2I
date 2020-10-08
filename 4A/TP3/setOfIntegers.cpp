#include "setOfIntegers.h"

#include <iostream>

using namespace std;

SetOfIntegers::SetOfIntegers(const size_t capacity) : _capacity(capacity) {
    _len = 0;
    _tab = new int[capacity];
}

SetOfIntegers::~SetOfIntegers() {
    delete _tab;
}

long SetOfIntegers::indexOf(const int elem) {
    for (size_t i = 0; i < _len; i++) {
        if (elem == _tab[i]) {
            return i;
        }
    }
    return -1;
}

void SetOfIntegers::add(const int elem) {
    if (indexOf(elem) == -1) {
        _tab[_len] = elem;
        _len++;
    }
}

void SetOfIntegers::remove(const int elem) {
    long index = indexOf(elem);
    if (index != -1) {
        for (size_t i = index; i < _len-1; i++) {
            _tab[i] = _tab[i+1];
        }
        _len--;
    }
}

size_t SetOfIntegers::cardinal() {
    return _len;
}

void SetOfIntegers::display() {
    cout << "{";
    for (size_t i = 0; i < _len; i++) {
        cout << _tab[i] << " ";
    }
    cout << "}" << endl;
}
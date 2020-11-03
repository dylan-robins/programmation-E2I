#include "string1.h"

#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

// CONSTRUCTORS

String::String() {
    _str = new char[_INIT_SIZE];
    _len = 0;
    _capacity = _INIT_SIZE;
    strcpy(_str, "");
}


String::String(const char c) {
    _str = new char[_INIT_SIZE];
    _len = 1;
    _capacity = _INIT_SIZE;
    _str[0] = c;
    _str[1] = '\0';
}

String::String(const char * buff) {
    unsigned long buff_size = strlen(buff);

    _str = new char[buff_size];
    _len = buff_size;
    _capacity = buff_size;
    strcpy(_str, buff);
}

String::String(const String& str) {
    _str = new char[str._capacity];
    _len = str._len;
    _capacity = str._capacity;
    strcpy(_str, str._str);
}

String::String(const unsigned long size) {
    _len = 0;
    _capacity = size;
    _str = new char[size];
    strcpy(_str, "");
}

String::String(const char c, const unsigned long size) {
    _str = new char[size];
    _len = size;
    _capacity = size;
    
    _str[0] = c;
    _str[1] = '\0';
}

String::String(const char * buff, const unsigned long size) {
    _str = new char[size];
    _len = size;
    _capacity = size;

    strncpy(_str, buff, size);
}

String::String(const String& str, const unsigned long size) {
    _str = new char[size];
    _len = size;
    _capacity = size;

    strncpy(_str, str._str, size);
}

// DESTRUCTOR
String::~String() {
    delete _str;
}

// CLASS METHODS

unsigned long String::longueur() const {
    return _len;
}
char& String::nieme(unsigned long i) const{
    return _str[i-1];
}
void String::affiche() const{
    cout << _str << endl;
}
void String::saisie() {
    cin >> _str;
}

void String::concatene(const char * suffix) {
    if (_len + strlen(suffix) > _capacity) {
        _extend(_len + strlen(suffix));
    }
    strcat(_str, suffix);
}

void String::concatene(const String& suffix) {
    if (_len + suffix.longueur() > _capacity) {
        _extend(_len + suffix.longueur());
    }
    strcat(_str, suffix._str);
}

String String::minuscule() const{
    String new_str(longueur());
    for (unsigned long i = 0; i < longueur(); i++) {
        new_str[i] = tolower(_str[i]);
    }
    return new_str;
}

char String::operator[](unsigned long i) const {
    return _str[i];
}
char& String::operator[](unsigned long i) {
    return _str[i];
}

void String::_extend(const unsigned long new_size) {
    // allouer nouveau char * assez grand
    char * new_str = new char[new_size];
    strcpy(new_str, _str);
    delete _str;

    _str = new_str;
    _len = new_size;
    _capacity = new_size;
}


ostream& operator<<(ostream& os, const String& str) {
    os << str._str;
    return os;
}


bool egal(const String& ch1, const String& ch2) {
    return (ch1.longueur() == ch2.longueur()) && strcmp(ch1._str, ch2._str) == 0;
}


String& String::operator=(const String& to_copy) {
    if (&to_copy != this) {
        _len = to_copy._len;
        _capacity = to_copy._capacity;
        _str = new char[_capacity];
        strncpy(_str, to_copy._str, _len);
    }
    return *this;
}
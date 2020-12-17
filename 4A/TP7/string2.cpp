#include "string2.h"

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

size_t String::_min_capacity = 50;

// Default constructor: creates an empty string.
String::String() : _str(nullptr) {
    _resize(_min_capacity);
    _len = 0;
}

// Copy constructor
String::String(const String& other) : _str(nullptr) {
    _resize(other._capacity);
    _len = other._len;
    strncpy(_str, other._str, _capacity);
}

String::String(const char* raw_str) : _str(nullptr) {
    size_t raw_len = strlen(raw_str);

    _resize(raw_len);
    _len = raw_len;
    strncpy(_str, raw_str, _capacity);
}

String::String(const char c) : _str(nullptr), _len(1) {
    _resize(_min_capacity);
    _str[0] = c;
    _str[1] = '\0';
}

String::String(const char c, const size_t capacity) : _str(nullptr), _len(1) {
    _resize(capacity);
    _str[0] = c;
    _str[1] = '\0';
}

// Default destructor: frees memory allocated to string
String::~String() {
    delete[] _str;
}

// Allocs a new array for the string and copies existing content across
void String::_resize(size_t new_size) {
    // store the address of the old array
    char * old_str = _str;

    // calculate effective size of array to alloc
    new_size = max(String::_min_capacity, new_size);

    // realloc array
    _str = new char[new_size];
    // verify that allocation went well
    if (_str == nullptr) {
        cerr << "Memory allocation failed" << endl;
        exit(EXIT_FAILURE);
    }

    _capacity = new_size;

    if (old_str != nullptr) {
        // copy old contents into new array
        strncpy(_str, old_str, _capacity);
        // free old array
        delete[] old_str;
    }
}

// renvoie la longueur de la chaine
size_t String::longueur() const {
    return _len;
}
// renvoie le nieme élément de la chaine
char& String::nieme(const size_t i) {
    return (*this)[i];
}

void String::affiche() const {
    cout << *this;
}

void String::saisie() {
    cin >> *this;
}

void String::concatene(const String& suffix) {
    *this += suffix;
}

String String::minuscule() const {
    String lowercase(*this);
    for (size_t i = 0; i < _len; i++) {
        lowercase[i] = tolower(lowercase[i]);
    }
    return lowercase;
}

// Returns the i-th char of the string
char String::operator[](size_t i) const {
    if (i < _len) {
        return _str[i];
    } else {
        cerr << "Error: accessing string index out of bounds" << endl;
        exit(EXIT_FAILURE);
    }
}
// Returns a reference to the i-th char of the string
char& String::operator[](size_t i) {
    if (i < _len) {
        return _str[i];
    } else {
        cerr << "Error: accessing string index out of bounds" << endl;
        exit(EXIT_FAILURE);
    }
}

// Assigns the contents of one string to the current one
String& String::operator=(const String& to_copy) {
    if (&to_copy != this) {
        _resize(to_copy._capacity);
        _len = to_copy._len;
        strncpy(_str, to_copy._str, _len);
    }
    return *this;
}

// Appends a string to the current one
String& String::operator+=(const String& to_append) {
    if (_capacity < _len+to_append._len) {
        // need to realloc: might as well rebuild everything
        cout << "Realloc'ing..." << endl;
        *this = *this + to_append;
    } else {
        // no need to realloc
        strncat(_str, to_append._str, _capacity);
        _len += to_append._len;
    }
    return *this;
}

// Inserts the string into an ostream
ostream& operator<<(ostream& os, const String& str) {
    os << str._str;
    return os;
}

// Extracts an istream into the string
istream& operator>>(istream& is, String& str) {
    char buffer[2048];
    is >> setw(2048) >> buffer;
    str._resize(strlen(buffer));
    strcpy(str._str, buffer);
    return is;
}

// Checks the equality of two strings
bool operator==(const String& str1, const String& str2) {
    return str1._len == str2._len && strncmp(str1._str, str2._str, str1._len);
}
bool operator!=(const String& str1, const String& str2) {
    return !(str1==str2);
}

// Concatenates two strings and returns the result
String operator+(const String& str1, const String& str2) {
    // create a new, empty string big enough to hold the concatenation
    String str3;
    str3._resize(str1._len+str2._len);
    str3._len = str1._len+str2._len;
    strncpy(str3._str, str1._str, str1._len);
    strncat(str3._str, str2._str, str2._len);
    return str3;
}
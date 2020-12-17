#ifndef __STRING_H__
#define __STRING_H__

#include <iostream>
using namespace std;

class String {
private:
    char* _str;
    size_t _len;       // length of the string
    size_t _capacity;  // size of the allocated array
    static size_t _min_capacity; // minimum allocation size to avoid repetedly realloc'ing

    void _resize(size_t new_size);

    friend ostream& operator<<(ostream& os, const String& str);
    friend istream& operator>>(istream& is, String& str);

    // in accordance with https://github.com/isocpp/CppCoreGuidelines/blob/036324/CppCoreGuidelines.md#c161-use-nonmember-functions-for-symmetric-operators
    friend bool operator==(const String& str1, const String& str2);
    friend bool operator!=(const String& str1, const String& str2);

    friend String operator+(const String& str1, const String& str2);

public:
    String();                // default constructor
    String(const String& other);  // copy constructor
    String(const char* raw_str);
    String(const char c);
    String(const char c, const size_t capacity);
    ~String();

    size_t longueur() const;
    char& nieme(const size_t i);
    void affiche() const;
    void saisie();
    void concatene(const String& suffix);
    String minuscule() const;

    char operator[](const size_t i) const;
    char& operator[](const size_t i);

    String& operator=(const String& to_copy);
    String& operator+=(const String& to_append);
};

#endif
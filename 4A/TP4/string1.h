#ifndef __STRING1_H__
#define __STRING1_H__

#include <iostream>

class String {
private:
    char * _str;
    unsigned long _len;
    unsigned long _capacity;
    void _extend(const unsigned long new_size);

    static const unsigned long _INIT_SIZE = 50;

    friend bool egal(const String& ch1, const String& ch2);
    friend std::ostream& operator<<(std::ostream& os, const String& str);
public:
    String();
    String(const char c);
    String(const char * buff);
    String(const String& str);
    String(const unsigned long size);
    String(const char c, const unsigned long size);
    String(const char * buff, const unsigned long size);
    String(const String& str, const unsigned long size);
    ~String();

    unsigned long longueur() const;
    char& nieme(unsigned long i) const;
    void affiche() const;
    void saisie();
    void concatene(const char * suffix);
    void concatene(const String& suffix);
    String minuscule() const;

    char operator[](const unsigned long i) const;
    char& operator[](const unsigned long i);
};

#endif
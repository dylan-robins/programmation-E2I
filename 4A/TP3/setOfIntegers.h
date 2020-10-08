#ifndef __SETOFINTEGERS_H__
#define __SETOFINTEGERS_H__

typedef unsigned long size_t;

class SetOfIntegers {
private:
    int *_tab;
    size_t _capacity;
    size_t _len;

public:
    SetOfIntegers() : _capacity(50) {};
    SetOfIntegers(const size_t capacity);
    ~SetOfIntegers();
    void add(const int elem);
    void remove(const int elem);
    long indexOf(const int elem);
    size_t cardinal();
    void display();
};

#endif
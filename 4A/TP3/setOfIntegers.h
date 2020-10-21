#ifndef __SETOFINTEGERS_H__
#define __SETOFINTEGERS_H__

typedef unsigned long size_t;

class Set_Of_Integer {
private:
    int *_tab;
    size_t _capacity;
    size_t _len;

public:
    Set_Of_Integer();
    Set_Of_Integer(const size_t capacity);
    ~Set_Of_Integer();
    void add(const int elem);
    void remove(const int elem);
    long indexOf(const int elem);
    size_t cardinal();
    void display();
};

#endif
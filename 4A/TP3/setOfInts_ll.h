#ifndef __SETOFINTS_LL_H__
#define __SETOFINTS_LL_H__

typedef unsigned long size_t;

class Node;

class SetOfInts_ll {
    friend Node;
private:
    Node *_tete;
    size_t _len;

public:
    SetOfInts_ll() : _tete(nullptr), _len(0){};
    ~SetOfInts_ll();
    void add(const int elem);
    void remove(const int elem);
    long indexOf(const int elem);
    size_t cardinal();
    void display();
};

class Node {
    friend SetOfInts_ll;
public:
    Node(const int val, Node *const next) : _val(val), _next(next) {};

    int _val;
    Node *_next;
};

#endif
#include "setOfInts_ll.h"

#include <iostream>

using namespace std;

SetOfInts_ll::~SetOfInts_ll() {
    Node *to_del;
    while (_tete != nullptr) {
        to_del = _tete;
        _tete = _tete->_next;
        delete to_del;
    }
}

long SetOfInts_ll::indexOf(const int elem) {
    Node *current = _tete;  // curseur pour parcourir la liste chainée
    long index = -1;
    // trouver l'élément à supprimer
    while (current != nullptr) {
        if (current->_val == elem) {
            // on l'a trouvé : arrêter de chercher
            break;
        }
        // avancer le curseur de parcours
        current = current->_next;
        index++;
    }
    return index;
}

void SetOfInts_ll::add(const int elem) {
    if (indexOf(elem) != -1) {
        Node *new_node = new Node(elem, _tete);
        _tete = new_node;
    }
}

void SetOfInts_ll::remove(const int elem) {
    Node *current = _tete;   // curseur pour parcourir la liste chainée
    Node *previous = _tete;  // curseur pour l'élément précédent (pour racoller la liste après l'élément supprimé)
    Node *to_del = nullptr;  // ptr temporaire pour faciliter la vie

    long index = indexOf(elem);

    // si l'élément a été trouvé
    if (index != -1) {
        // avancer jusqu'à l'élément
        for (long i = 0; i < index; i++) {
            previous = current;
            current = current->_next;
        }
        // supprimer l'élément
        to_del = current;
        previous->_next = current->_next;
        delete current;
    }
}

size_t SetOfInts_ll::cardinal() {
    return _len;
}

void SetOfInts_ll::display() {
    Node *current = _tete;   // curseur pour parcourir la liste chainée

    cout << "{";
    while (current != nullptr) {
        cout << current->_val << " ";
    }
    cout << "}";
}

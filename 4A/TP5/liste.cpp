#include "liste.h"

#include <iostream>

Liste::Liste() {
    _debut = nullptr;
}

Liste::~Liste() {
    while (_debut != nullptr) {
        _courant = _debut;
        _debut = _debut->suivant;
        delete _courant;
    }
}

void Liste::ajoute(void * el_ptr) {
    element * nouveau = new element;
    nouveau->contenu = el_ptr;
    nouveau->suivant = _debut;
    _debut = nouveau;
}

void * Liste::premier() {
    _courant = _debut;
    return _courant->contenu;
}

void * Liste::prochain() {
    _courant = _courant->suivant;
    return _courant->contenu;
}

bool Liste::fini() {
    return (_courant->suivant == nullptr);
}
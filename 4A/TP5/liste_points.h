#ifndef __LISTE_POINTS_H__
#define __LISTE_POINTS_H__

#include "liste.h"
#include "point.h"

class ListePoints : public Liste {
    public:
        ListePoints() : Liste() {};
        void afficher();
};

ListePoints::ListePoints(/* args */) {
}

ListePoints::~ListePoints() {
}

#endif
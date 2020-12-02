#ifndef __LISTE_POINTS_H__
#define __LISTE_POINTS_H__

#include "liste.h"
#include "points.h"

class ListePoints : public Liste {
    public:
        ListePoints() : Liste() {};
        void afficher();
};

#endif
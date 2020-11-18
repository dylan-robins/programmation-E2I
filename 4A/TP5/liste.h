#ifndef __LISTE_H__
#define __LISTE_H__

struct element {
    element *suivant;
    void *contenu;
};

class Liste {
    public:
        Liste();
        ~Liste();
        void ajoute(void *);
        void *premier();
        void *prochain();
        bool fini();

    private:
        element *_debut;
        element *_courant;
};

#endif
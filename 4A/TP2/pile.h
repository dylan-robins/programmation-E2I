class Pile {
public:
    Pile(int max) : _max(max) {
        _nb_elem = 0;
        _etat = vide;
        _table = new int[max];

        _nb_objets++;
    }
    ~Pile() { delete[] _table; }
    void empiler(int);
    int depiler();
    void afficher();
    int nb_elements();

    static int nb_objets() { return _nb_objets; }

private:
    const int _max;
    int* _table;
    int _nb_elem;
    enum pile_etat { ok,
                     plein,
                     vide };
    pile_etat _etat;

    static int _nb_objets;
};
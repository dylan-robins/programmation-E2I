class Vecteur3d {
public:
    Vecteur3d();
    Vecteur3d(const double x, const double y, const double z);
    Vecteur3d(const Vecteur3d &a_copier);
    ~Vecteur3d() {}
    void afficher() const;
private:
    double _x;
    double _y;
    double _z;
};
class salarie {
   public:
    salarie(const char *nom, int bureau = 0);
    ~salarie();
    void afficher();
    void set_bureau(int bureau);
    const char *get_telephone();
    static unsigned long get_nb_salaries();

   private:
    char *_nom;
    int _bureau;
    static unsigned long _nb_salaries;
};

class employe : public salarie {
   public:
    employe(const char *nom, int bureau = 0, float taux_horaire = 0.0, float nb_heures = 0.0);
    ~employe();
    void afficher();
    void set_taux(float taux_horaire);
    void set_heures(float nb_heures);
    float calcul_salaire();
    static unsigned long get_nb_employes();
           
   private:
    float _taux_horaire;
    float _nb_heures;
    static unsigned long _nb_employes;
};

class commercial : public employe {
   public:
    commercial(const char *nom, float chiffre_affaire, int bureau = 0, float taux_horaire = 0.0,
               float nb_heures = 0.0, float pourcentage = 0.0);
    ~commercial();
    void afficher();
    void set_pourcentage(float pourcentage);
    void set_chiffre_affaire(float chiffre_affaire);
    float calcul_salaire();
    static unsigned long get_nb_commerciaux();

   private:
    float _pourcentage;
    float _chiffre_affaire;
    static unsigned long _nb_commerciaux;
};

class directeur : public salarie {
   public:
    directeur(const char *nom, int bureau = 0, float fixe = 0.0,
              float prime = 0.0, int nb_employe = 0);
    ~directeur();
    void afficher();
    void set_fixe(float fixe);
    void set_prime(float prime);
    void set_nb_employe(int nb_employe);
    float calcul_salaire();
    static unsigned long get_nb_directeurs();

   private:
    float _fixe;
    float _prime;
    int _nb_employe;
    static unsigned long _nb_directeurs;
};
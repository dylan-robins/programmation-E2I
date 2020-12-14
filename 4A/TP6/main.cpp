#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define EX1
#define EX2
#define EX3

int read_num() {
    int n;
    cout << "Entrez un nombre entier (0 pour quitter):" << endl << ">>> ";
    cin >> n;
    return n;
}

void write_bin_file(string filename) {
    ofstream ofile(filename, ios::out | ios::binary);
    int tmp = -1;

    if (!ofile.is_open()) {
        cerr << "Erreur: impossible d'ouvrir le fichier \"" << filename << '"' << endl;
        exit(EXIT_FAILURE);
    }

    // lire des nombres jusqu'à trouver un 0
    while ((tmp = read_num()) != 0) {
        ofile.write((char *)(&tmp), sizeof(tmp));
    }
    
    ofile.close();
}

void read_bin_file(string filename) {
    ifstream ifile(filename, ios::in | ios::binary);
    int tmp;
    int i = 0;

    if (!ifile.is_open()) {
        cerr << "Erreur: impossible d'ouvrir le fichier \"" << filename << '"' << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Le fichier contient les nombres [";
    
    while (true) {
        // tenter de lire un entier
        ifile.read((char *)(&tmp), sizeof(tmp));
        // si on a atteint la fin du fichier, sortir de la boucle
        if (ifile.eof()) break;
        // afficher l'entier
        cout << tmp << ", ";
    }

    // Effacer le ", " final et afficher un ']' à la place
    cout << "\b\b]" << endl;
    
    ifile.close();
}

void get_ints_from_bin_file(string filename) {
    ifstream ifile(filename, ios::in | ios::binary);
    int index, val;

    if (!ifile.is_open()) {
        cerr << "Erreur: impossible d'ouvrir le fichier \"" << filename << '"' << endl;
        exit(EXIT_FAILURE);
    }

    while ((index = read_num()) != 0) {
        // vu qu'on indexe le fichier à partir de 1, on doit soustraire 1 pour
        // retomber sur un décalage qui a du sens...
        index--; 
        
        ifile.seekg(index*sizeof(index), ios_base::beg);
        ifile.read((char *)&val, sizeof(val));

        // vérification de "l'indice"
        if (ifile.eof()) {
            cerr << "Erreur de dépassement: impossible d'accéder à l'élément " << index << endl;
            ifile.clear();
        } else {
            cout << "nombre à l'indice " << index+1 << ": " << val << endl;
        }
    }
    
    ifile.close();
}

int main(void) {
    string filename;
    cout << "Entrez le nom du fichier à manipuler:" << endl 
         << ">>> ";
    cin >> filename;

#ifdef EX1
    cout << endl
         << "##########  Exercice 1: Ecriture dans un fichier binaire ##########" << endl;
    write_bin_file(filename);
#endif

#ifdef EX2
    cout << endl
         << "##########  Exercice 2: Lecture du fichier binaire ################" << endl;
    read_bin_file(filename);
#endif

#ifdef EX3
    cout << endl
         << "########## Exercice 3: Accès par indice ###########################" << endl;
    get_ints_from_bin_file(filename);
#endif
    return 0;
}
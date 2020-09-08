#include <iostream>
#include <cstring>

using namespace std;

char **lire_phrases(const int nb_phrases) {
    char buffer[200];
    
    // allouer tableau de phrases
    char **phrases = new char*[nb_phrases];

    for (int i = 0; i < nb_phrases; i++) {
        cout << "Entrez une phrase (max 200 caractères)";
        cin >> buffer;
        phrases[i] = new char[strlen(buffer)];
        strcpy(phrases[i], buffer);
    }

    return phrases;
}

void inverser_phrases(char **phrases, const int nb_phrases) {
    char * tmp;
    for (int i = 0; i < nb_phrases/2; i++) {
        tmp = phrases[i];
        phrases[i] = phrases[nb_phrases-1-i];
        phrases[nb_phrases-1-i] = tmp;
    }
}

char ** lire_mots(const int nb_mots) {
    char ** mots = new char*[nb_mots];
    for (int i = 0; i < nb_mots; i++) {
        mots[i] = new char[50];
        cout << "Entrez un mot (max 50 caractères): ";
        cin >> mots[i];
    }
    return mots;
}

bool ordre_bon(const char * A, const char * B) {
    if (isalpha(A[0]) && isalpha(B[0]) && tolower(A[0]) == tolower(B[0])) {
        // Lettres identiques - on teste la lettre suivante
        return ordre_bon(A+1, B+1);
    } else if (A[0] != '\0' && B[0] == '\0') {
        // si A plus long que B mais sinon identique
        return false;
    } else if (A[0] == '\0') {
        // si B plus long que A mais identique
        // ou longueurs identiques
        return true;
    } else {
        // si comparaison possible
        return tolower(A[0]) <= tolower(B[0]);
    }
}

void trier_mots(char ** mots, const int nb_mots) {
    char * tmp;
    bool sorted = false;
    int iteration = 0;
    // tri a bulles - lent mais facile (j'ai la flemme)
    while (!sorted) {
        sorted = true;

        for (int i = 1; i < nb_mots-iteration; i++) {
            if (!ordre_bon(mots[i-1], mots[i])) {
                // inverser les mots
                tmp = mots[i-1];
                mots[i-1] = mots[i];
                mots[i] = tmp;
                sorted = false;
            }
        }
    }
}

char * pop_mot(char ** mots, const int nb_mots) {
    char * mot = mots[0];
    for (int i = 0; i < nb_mots-1; i++) {
        mots[i] = mots[i+1];
    }
    return mot;
}

int main(void) {
    // partie 1
    char **phrases = lire_phrases(10);
    cout << "Phrases initiales :" << endl;
    for (int i = 0; i < 10; i++) {
        cout << phrases[i] << endl;
    }
    inverser_phrases(phrases, 10);
    cout << "Phrases inversées :" << endl;
    for (int i = 0; i < 10; i++) {
        cout << phrases[i] << endl;
        // cleanup
        delete phrases[i];
    }
    delete phrases;
    
    // partie 2
    int nb_mots = 10;
    char ** mots = lire_mots(nb_mots);
    
    cout << "Liste de mots : ";
    for (int i = 0; i < nb_mots; i++) {
        cout << mots[i] << " ";
    }
    cout << endl;

    trier_mots(mots, nb_mots);
    
    cout << "Liste de mots triée : ";
    for (int i = 0; i < nb_mots; i++) {
        cout << mots[i] << " ";
    }
    cout << endl;

    while (nb_mots > 0) {
        cout << "Suppression de la phrase \"" << pop_mot(mots, nb_mots) << '"' << endl;
        nb_mots--;
        cout << nb_mots << " mots restants. Appuyez sur entrée pour continuer";
        cin.get(); // attendre d'appuyer sur une touche
    }

    for (int i = 0; i < nb_mots; i++) {
        delete mots[i];
    }
    delete mots;

    return 0;
}
#include <iostream>

#include "fileof.h"
#include "forme.h"
#include "string2.h"

#define EX3
#define EX3_float

int main(void) {
#ifdef EX1
    cout << "################################# Exercice 1 ##################################" << endl;
    String ch1("essai");
    String ch2 = ch1;
    String ch3('=', 80);
    const String ch4("chaîne de caractères constante");
    ch1[0] = 'E'; // le premier caractère de la chaîne
    cout << "ch1 modifié: " << ch1 << endl;
    cout << ch4[0] << endl;
    ch1 = "<<<< " + ch2 + " >>>>";
    cout << ch1 << endl;
    cin >> ch2;
    ch2 += " de la classe Strin";
    ch2 += 'g';
    if (ch2 != "")
        cout << ch2 << endl;
    cout << ch2.minuscule() << endl;
#endif

#ifdef EX2
    cout << "################################# Exercice 2 ##################################" << endl;
    Circle cercle(10, 10, 4);
    cout << endl;
    cout << cercle << ", surface=" << cercle.area() << endl;

    Triangle triangle(20, 20, 3);
    cout << endl;
    cout << triangle << ", surface=" << triangle.area() << endl;

    Rectangle rectangle(30, 30, 2, 5);
    cout << endl;
    cout << rectangle << ", surface=" << area(rectangle) << endl;

    Square *s = new Square(100, 100, 2);
    cout << endl;
    cout << *s << ", surface=" << s->area() << endl;

    cout << endl;
    cercle.translate(50, 50);
    cout << "déplacement " << endl;
    cout << cercle << endl
         << endl;

    Shape *tab[4];
    tab[0] = &cercle;
    tab[1] = &triangle;
    tab[2] = &rectangle;
    tab[3] = s;

    float surf = 0.0;
    for (int i = 0; i < 4; i++) {
        surf += tab[i]->area();
    }
    cout << "surface totale : " << surf << endl
         << endl;

    cout << "périmètre d'une forme tirée au hasard" << endl;
    srand((unsigned int)time(NULL));
    Shape *ptr = tab[rand() % 4]; // définition de ptr
    cout << *ptr << " périmètre=" << ptr->perimeter() << endl
         << endl;

    cout << "destruction de carré alloué dynamiquement" << endl;
    delete s;
#endif
#ifdef EX3
    cout << "################################# Exercice 3 ##################################" << endl;

    W_File_of_Int<int> f_out("essai.fic");
    if (!f_out) {
        cerr << "erreur à la création de 'essai.fic'\n";
        return 1;
    }
    for (int i = 0; i <= 10; i++) // Ecriture de 11 entiers dans le fichier
        f_out << i;
    cout << f_out.tellp() << " éléments sont écrits dans le fichier.\n"; // affiche:  11 éléments sont écrits dans le fichier.
    f_out.close();
    cout << endl;
    /////////////////////////////////////////////////////////////////

    R_File_of_Int<int> f_in("essai.fic");
    int entier;
    if (!f_in) {
        cerr << "erreur à la création de essai.fic\n";
        return 1;
    }
    f_in.seekg(0, ios::end);                                             // se positionne à la fin du fichier
    cout << "Il y a " << f_in.tellg() << " éléments dans le fichier.\n"; // affiche:  Il y a 11 éléments dans le fichier.
    f_in.seekg(0);                                                       // se positionne au début du fichier
    while (1) {                                                          // affichage du contenu du fichier
        f_in >> entier;
        if (f_in.eof())
            break;
        cout << entier << " ";
    }
    f_in.clear(); // ne pas l'oublier ... sortie du while sur erreur eof
    cout << endl;
    f_in.close();
    cout << endl;
    /////////////////////////////////////////////////////////////////

    RW_File_of_Int<int> f_io("essai.fic"); //s’il existe, il n'est pas écrasé
    if (!f_io) {
        cerr << "erreur à la création de essai.fic\n";
        return 1;
    }
    f_io.seekp(0, ios::end);                                                 // se positionne à la fin du fichier
    cout << "Il y a déjà " << f_io.tellp() << " éléments dans le fichier\n"; // affiche:  Il y a déjà 11 éléments dans le fichier
    for (int i = 11; i <= 19; i++)
        f_io << i;
    f_io.seekp(10); // se positionne sur le 11 ième entier
    while (1) {     // affichage du contenu du fichier
        f_io >> entier;
        if (f_io.eof())
            break;
        cout << entier << " ";
    }             // affiche:  10 11 12 13 14 15 16 17 18 19
    f_io.clear(); // ne pas l'oublier...sortie du while sur erreur eof
    f_io.close();
    cout << endl;
#endif
#ifdef EX3_float
    cout << "######################### Exercice 3 - avec des floats ########################" << endl;

    W_File_of_Int<float> f_out_float("essai.fic");
    if (!f_out_float) {
        cerr << "erreur à la création de 'essai.fic'\n";
        return 1;
    }
    for (int i = 0; i <= 10; i++) // Ecriture de 11 floats dans le fichier
        f_out_float << i + 0.2;
    cout << f_out_float.tellp() << " éléments sont écrits dans le fichier.\n"; // affiche:  11 éléments sont écrits dans le fichier.
    f_out_float.close();
    cout << endl;
    /////////////////////////////////////////////////////////////////

    R_File_of_Int<float> f_in_float("essai.fic");
    float n;
    if (!f_in_float) {
        cerr << "erreur à la création de essai.fic\n";
        return 1;
    }
    f_in_float.seekg(0, ios::end);                                             // se positionne à la fin du fichier
    cout << "Il y a " << f_in_float.tellg() << " éléments dans le fichier.\n"; // affiche:  Il y a 11 éléments dans le fichier.
    f_in_float.seekg(0);                                                       // se positionne au début du fichier
    while (1) {                                                                // affichage du contenu du fichier
        f_in_float >> n;
        if (f_in_float.eof())
            break;
        cout << n << " ";
    }
    f_in_float.clear(); // ne pas l'oublier ... sortie du while sur erreur eof
    cout << endl;
    f_in_float.close();
    cout << endl;
    /////////////////////////////////////////////////////////////////

    RW_File_of_Int<float> f_io_float("essai.fic"); //s’il existe, il n'est pas écrasé
    if (!f_io_float) {
        cerr << "erreur à la création de essai.fic\n";
        return 1;
    }
    f_io_float.seekp(0, ios::end);                                                 // se positionne à la fin du fichier
    cout << "Il y a déjà " << f_io_float.tellp() << " éléments dans le fichier\n"; // affiche:  Il y a déjà 11 éléments dans le fichier
    for (int i = 11; i <= 19; i++)
        f_io_float << i + 0.2;
    f_io_float.seekp(10); // se positionne sur le 11 ième entier
    while (1) {           // affichage du contenu du fichier
        f_io_float >> n;
        if (f_io_float.eof())
            break;
        cout << n << " ";
    }                   // affiche:  10 11 12 13 14 15 16 17 18 19
    f_io_float.clear(); // ne pas l'oublier...sortie du while sur erreur eof
    f_io_float.close();
    cout << endl;
#endif

    return 0;
}

#include <iostream>

#include "string2.h"

#define EX1

int main(void) {
#ifdef EX1
    String ch1("essai");
    String ch2 = ch1;
    String ch3('=', 80);
    const String ch4("chaîne de caractères constante");
    ch1[0] = 'E';  // le premier caractère de la chaîne
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
    return 0;
}
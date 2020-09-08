#include <iostream>
#include <random>

using namespace std;

long somme(int *tab, const int len) {
    long s = 0;
    for (int i = 0; i < len; i++) {
        s += tab[i];
    }
    return s;
}

int main(void) {
    int tab[10];

    // init rng
    random_device rd;
    uniform_int_distribution<int> dist(0, 100);
    
    // populer tab avec 0 entiers au pif
    cout << "Liste: ";
    for (int i = 0; i < 10; i++) {
        tab[i] = dist(rd);
        cout << tab[i] << " ";
    }
    cout << endl;

    cout << "Somme: " << somme(tab, 10) << endl;

    return 0;
}
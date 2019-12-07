#include <stdio.h>

int main() {
    int a;
    char c = 'a';
    while (c != 'q') {
        scanf("%d", &a);
        getchar();
        printf("La valeur entree au clavier est : %d\n", a);
        printf("q pour quitter : \n");
        scanf("%c", &c);
        getchar();
    }
	return 0;
}

#include <stdio.h>

struct Busca {
    int valores[10];
};

void Bolha(struct Busca *busca) {
    int i, aux;
    int tam = sizeof(busca->valores) / sizeof(busca->valores[0]);
    while (tam > 1) {
        for (i = 0; i < tam - 1; i++) {
            if (busca->valores[i] > busca->valores[i + 1]) {
                aux = busca->valores[i];
                busca->valores[i] = busca->valores[i + 1];
                busca->valores[i + 1] = aux;
            }
        }
        tam = tam - 1;
    }
}

int main() {
    struct Busca busca = { .valores = {1, 2, 4, 5, 7, 6, 3, 9, 8, 0} };
    
    printf("Vetor sem ordenacao:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d, ", busca.valores[i]);
    }
    printf("\n\n");
    
    Bolha(&busca);
    
    printf("Vetor ordenado:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d, ", busca.valores[i]);
    }
    printf("\n");

    return 0;
}

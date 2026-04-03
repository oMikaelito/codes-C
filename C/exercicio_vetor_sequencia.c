#include <stdio.h>
#include <stdbool.h>

bool verificarRepeticao(int sequencia[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho - 1; j++) {
            if (sequencia[i] == sequencia[j] && sequencia[i + 1] == sequencia[j + 1]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int tamanho;

    printf("Digite o tamanho da sequencia: ");
    scanf("%d", &tamanho);

    int sequencia[tamanho];

    printf("Digite os elementos da sequencia: ");
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", &sequencia[i]);
    }

    if (verificarRepeticao(sequencia, tamanho)) {
        printf("Sim, possui uma sequencia de 2.\n");
    } else {
        printf("Nao, nao possui uma sequencia de 2.\n");
    }

    return 0;
}

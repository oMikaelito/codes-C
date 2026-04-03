#include <stdio.h>

void imprimirMapa(int mapa[10][10]) {
    int linha, coluna;

    for (linha = 0; linha < 10; linha++) {
        for (coluna = 0; coluna < 10; coluna++) {
            if (coluna == 0) {
                printf("\n");
            }
            printf("%d ", mapa[linha][coluna]);
        }     
    }
    printf("\n");
}

void inicializarMapa(int mapa[10][10]) {
    int linha, coluna;

    for (linha = 0; linha < 10; linha++) {
        for (coluna = 0; coluna < 10; coluna++) {
            mapa[linha][coluna] = 0;
        }
    }
}

void colocarUm(int mapa[10][10], int linha, int coluna) {
    if (linha >= 0 && linha < 10 && coluna >= 0 && coluna < 10) {
        mapa[linha][coluna] = 1;
    } else {
        printf("Posicao (%d, %d) invalida. Tente novamente.\n", linha, coluna);
    }
}

int main() {
    int mapa[10][10];
    int i, linha, coluna;

    inicializarMapa(mapa);

    for (i = 0; i < 3; i++) {
        printf("Digite a posicao %d (linha e coluna) para colocar o numero 1: ", i + 1);
        scanf("%d %d", &linha, &coluna);
        colocarUm(mapa, linha, coluna);
    }

    imprimirMapa(mapa);

    return 0;
}

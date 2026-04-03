#include <stdio.h>

void criarMapa(int mapaJogador[10][10]) {
    int linha, coluna;

    for (linha = 0; linha < 10; linha++) {
        for (coluna = 0; coluna < 10; coluna++) {
            mapaJogador[linha][coluna] = 0;
        }
    }

    for (linha = 0; linha < 10; linha++) {
        for (coluna = 0; coluna < 10; coluna++) {
            if (coluna == 0) {
                printf("\n");
            }
            printf("%d ", mapaJogador[linha][coluna]);
        }     
    }
    printf("\n"); // Ensure a newline at the end of the map
}

int main() {
    int mapaJ1[10][10];
    int mapaJ2[10][10];
    criarMapa(mapaJ1);
    criarMapa(mapaJ2);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void initializeBoard(int board[SIZE][SIZE]);
void printBoard(int board[SIZE][SIZE], int revealShips);
void placeShips(int board[SIZE][SIZE], int player);
int attack(int board[SIZE][SIZE], int row, int col);
int allShipsSunk(int board[SIZE][SIZE]);

int main() {
    int player1Board[SIZE][SIZE];
    int player2Board[SIZE][SIZE];
    int currentPlayer = 1;
    int row, col;
    int gameOver = 0;

    initializeBoard(player1Board);
    initializeBoard(player2Board);

    printf("Player 1, place your ships.\n");
    placeShips(player1Board, 1);

    printf("Player 2, place your ships.\n");
    placeShips(player2Board, 2);

    while (!gameOver) {
        if (currentPlayer == 1) {
            printf("Player 1's turn to attack.\n");
            printBoard(player2Board, 0);
            printf("Enter row and column to attack: ");
            scanf("%d %d", &row, &col);
            if (attack(player2Board, row, col)) {
                printf("Hit!\n");
            } else {
                printf("Miss.\n");
            }
            if (allShipsSunk(player2Board)) {
                printf("Player 1 wins!\n");
                gameOver = 1;
            }
            currentPlayer = 2;
        } else {
            printf("Player 2's turn to attack.\n");
            printBoard(player1Board, 0);
            printf("Enter row and column to attack: ");
            scanf("%d %d", &row, &col);
            if (attack(player1Board, row, col)) {
                printf("Hit!\n");
            } else {
                printf("Miss.\n");
            }
            if (allShipsSunk(player1Board)) {
                printf("Player 2 wins!\n");
                gameOver = 1;
            }
            currentPlayer = 1;
        }
    }

    return 0;
}

void initializeBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

void printBoard(int board[SIZE][SIZE], int revealShips) {
    printf("  ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 1) {
                printf("X ");
            } else if (board[i][j] == 0) {
                printf(". ");
            } else {
                if (revealShips) {
                    printf("%d ", board[i][j]);
                } else {
                    printf(". ");
                }
            }
        }
        printf("\n");
    }
}

void placeShips(int board[SIZE][SIZE], int player) {
    int shipSizes[] = {5, 4, 4, 3, 3, 3, 2, 2, 2, 2};
    int numShips = 10;
    int row, col, orientation;

    for (int i = 0; i < numShips; i++) {
        int size = shipSizes[i];
        int placed = 0;

        while (!placed) {
            printf("Enter row, column, and orientation (0 for horizontal, 1 for vertical) for ship of size %d: ", size);
            scanf("%d %d %d", &row, &col, &orientation);

            if (orientation == 0) { // Horizontal
                if (col + size <= SIZE) {
                    int canPlace = 1;
                    for (int j = 0; j < size; j++) {
                        if (board[row][col + j] != 0) {
                            canPlace = 0;
                            break;
                        }
                    }
                    if (canPlace) {
                        for (int j = 0; j < size; j++) {
                            board[row][col + j] = size;
                        }
                        placed = 1;
                    }
                }
            } else { // Vertical
                if (row + size <= SIZE) {
                    int canPlace = 1;
                    for (int j = 0; j < size; j++) {
                        if (board[row + j][col] != 0) {
                            canPlace = 0;
                            break;
                        }
                    }
                    if (canPlace) {
                        for (int j = 0; j < size; j++) {
                            board[row + j][col] = size;
                        }
                        placed = 1;
                    }
                }
            }
            if (!placed) {
                printf("Cannot place ship there. Try again.\n");
            }
        }
    }
}

int attack(int board[SIZE][SIZE], int row, int col) {
    if (board[row][col] > 1) {
        int ship = board[row][col];
        board[row][col] = ship;
        return 1;
    } else {
        board[row][col] = 1;
        return 0;
    }
}

int allShipsSunk(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] > 1) {
                return 0;
            }
        }
    }
    return 1;
}
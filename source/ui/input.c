#include "input.h"
#include "move.h"
#include <stdio.h>

int input_get_board_dimensions(int *rows, int *cols) {
    printf("\nDigite o numero de linhas e colunas do tabuleiro:\n");
    printf("\nO numero de linhas e colunas devem ser pares e iguais!\n");
    scanf("%d %d", rows, cols);

    while (*rows != *cols || *cols <= 0 || *rows >= 10 || *cols >= 10 || *rows % 2 != 0 || *cols % 2 != 0) {
        printf("\nDimensoes invalidas!\n");
        scanf("%d %d", rows, cols);
    }

    return 0;
}

int input_select_row(int max_row) {
    int row;
    printf("Selecione a linha (1 a %d):\n", max_row);
    scanf("%d", &row);

    while (row < 1 || row > max_row) {
        printf("Linha invalida, por favor, digite uma linha valida!\n");
        scanf("%d", &row);
    }

    return row - 1;
}

int input_select_col(int max_col) {
    int col;
    printf("Selecione a coluna (1 a %d):\n", max_col);
    scanf("%d", &col);

    while (col < 1 || col > max_col) {
        printf("Coluna invalida, por favor, digite uma coluna valida!\n");
        scanf("%d", &col);
    }

    return col - 1;
}

PlayedHand *input_get_played_positions(int hand_size) {
    PlayedHand *positions = create_played_hand(hand_size);

    for (int i = 0; i < hand_size; i++) {
        int row, col;
        printf("\nDigite a linha da %d° jogada: ", i + 1);
        scanf("%d", &row);

        printf("Digite a coluna da %d° jogada: ", i + 1);
        scanf("%d", &col);

        positions[i].row = row - 1;
        positions[i].col = col - 1;
    }

    return positions;
}
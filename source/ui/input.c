#include "input.h"
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
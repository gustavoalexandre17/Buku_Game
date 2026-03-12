#include "../../include/ui/input.h"
#include "../../include/move.h"
#include <stdio.h>

int input_get_board_dimensions(int *rows, int *cols) {
    printf("\nDigite o numero de linhas e colunas do tabuleiro:\n");
    printf("\nO numero de linhas e colunas devem ser pares e iguais!\n");

    while (1) {
        *rows = get_single_int("Linhas: ");
        *cols = get_single_int("Colunas: ");

        if (*rows >= 2 && *cols >= 2 && *rows == *cols && *rows % 2 == 0 && *cols % 2 == 0) {
            printf("Linhas e Colunas váidas, inicializando tabuleiro... \n");
            break;
        } else {
            printf("Linha ou Coluna inválida! \n");
        }
    }

    return 0;
}

int input_select_row(int max_row) {
    int row;
    printf("Selecione a linha (1 a %d): ", max_row);
    row = get_single_int("");

    while (row < 1 || row > max_row) {
        printf("Linha invalida, por favor, digite uma linha valida!\n");
        printf("Selecione a linha (1 a %d): ", max_row);

        row = get_single_int("");
    }

    return row - 1;
}

int input_select_col(int max_col) {
    int col;
    printf("Selecione a coluna (1 a %d):\n", max_col);
    col = get_single_int("");

    while (col < 1 || col > max_col) {
        printf("Coluna invalida, por favor, digite uma coluna valida!\n");
        col = get_single_int("");
    }

    return col - 1;
}

PlayedHand *input_get_played_positions(int hand_size) {
    PlayedHand *positions = create_played_hand(hand_size);

    if (positions == NULL)
        return NULL;

    if (hand_size == 0)
        return positions;

    for (int i = 0; i < hand_size; i++) {
        int row, col;
        printf("\nDigite a linha da %d° jogada: ", i + 1);
        row = get_single_int("");

        printf("Digite a coluna da %d° jogada: ", i + 1);
        col = get_single_int("");

        positions[i].row = row - 1;
        positions[i].col = col - 1;
    }

    return positions;
}

int get_single_int(char *input) {
    char buffer[256];
    int value;

    while (1) {
        printf("%s", input);

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &value) == 1) {
                return value;
            }
        }
        printf("Comando invalido! Digite apenas um numero inteiro.\n");
    }
}

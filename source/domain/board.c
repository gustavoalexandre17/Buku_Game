#include "../../include/domain/board.h"
#include <stdio.h>
#include <stdlib.h>

Board *create_board(int rows, int cols) {

    Board *new_board = (Board *)malloc(sizeof(Board));

    if (!new_board)
        return NULL;

    new_board->rows = rows;
    new_board->cols = cols;
    new_board->turns = 1;
    new_board->cells = (Stack ***)malloc(rows * sizeof(Stack **));

    if (!new_board->cells)
        return NULL;

    for (int i = 0; i < rows; i++) {
        new_board->cells[i] = (Stack **)malloc(cols * sizeof(Stack *));
        if (!new_board->cells[i]) {
            destroy_board_partial(new_board, i, cols);
            return NULL;
        }

        for (int j = 0; j < cols; j++) {
            new_board->cells[i][j] = create_stack();
            if (!new_board->cells[i][j]) {
                destroy_board_partial(new_board, i + 1, j);
                return NULL;
            }
        }
    }
    printf("\nTabuleiro criado com sucesso!\n");
    return new_board;
}

int init_board(Board *b) {
    if (!b)
        return -1;

    for (int i = 0; i < b->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            insert_stack(b->cells[i][j], 'O');

            if (i % 2 == 0)
                j % 2 == 0 ? st_set_color(b->cells[i][j], 'v') : st_set_color(b->cells[i][j], 'a');
            else
                j % 2 == 0 ? st_set_color(b->cells[i][j], 'a') : st_set_color(b->cells[i][j], 'v');
        }
    }
    return 0;
}

/*  Essa funcao serve apenas para tratar eventuais erros de alocacao durante a criacao do tabuleiro,
    desfazendo todas as alocacoes anteriores a que gerou erro.
*/

int destroy_board_partial(Board *b, int rows_filled, int cols_filled) {
    if (!b)
        return -1;

    for (int i = 0; i < rows_filled; i++) {
        for (int j = 0; j < cols_filled; j++)
            free_stack(b->cells[i][j]);
        free(b->cells[i]);
    }
    free(b->cells);

    return 0;
}

int destroy_board(Board *b) {
    if (!b)
        return -1;

    for (int i = 0; i < b->rows; i++) {
        for (int j = 0; j < b->cols; j++)
            free_stack(b->cells[i][j]);
        free(b->cells[i]);
    }
    free(b->cells);

    return 0;
}

int fill_board(Board *b) {
    if (!b)
        return -1;

    for (int i = 0; i < b->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            insert_stack(b->cells[i][j], 'O');
        }
    }
    return 1;
}

int view_board_size(Board *b) {
    if (b == NULL)
        return -1;
    return b->rows;
}

Board *copy_board(Board *b) {
    Board *copy = create_board(b->rows, b->cols);
    if (!copy) return NULL;

    for (int i = 0; i < b->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            Stack *original = b->cells[i][j];
            Stack *new_stack = copy->cells[i][j];

           // while (st_view_size(new_stack) > 0) pop_stack(new_stack);
            for (int k = 0; k < st_view_size(original); k++) {
                insert_stack(new_stack, 'O');
            }
            st_set_color(new_stack, st_view_color(original));
        }
    }
    return copy;
}

bool boards_equal(Board *b1, Board *b2) {
    if (b1->rows != b2->rows || b1->cols != b2->cols) return false;

    for (int i = 0; i < b1->rows; i++) {
        for (int j = 0; j < b1->cols; j++) {
            Stack *s1 = b1->cells[i][j];
            Stack *s2 = b2->cells[i][j];

            if (st_view_size(s1) != st_view_size(s2)) return false;
            if (st_view_color(s1) != st_view_color(s2)) return false;
        }
    }
    return true;
}

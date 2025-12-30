#include "../include/board.h"
#include <stdio.h>
#include <stdlib.h>

Board createBoard(int rows, int cols)
{
    Board new_board;

    new_board.rows = rows;
    new_board.cols = cols;

    new_board.cells = (stack ***)malloc(rows * sizeof(stack **));
    if (!new_board.cells)
        return (Board){0}; // O equivalente ao NULL para o struct board

    for (int i = 0; i < rows; i++)
    {
        new_board.cells[i] = (stack **)malloc(cols * sizeof(stack *));
        if (!new_board.cells[i])
        {
            destroyBoardPartial(&new_board, i, cols);
            return (Board){0};
        }

        for (int j = 0; j < cols; j++)
        {
            new_board.cells[i][j] = create_stack();
            if (!new_board.cells[i][j])
            {
                destroyBoardPartial(&new_board, i + 1, j);
                return (Board){0};
            }
        }
    }
    return new_board;
}

void initBoard(Board *b)
{
    for (int i = 0; i < b->rows; i++)
    {
        for (int j = 0; j < b->cols; j++)
        {
            insert_stack(b->cells[i][j], TOKEN);

            if (i % 2 == 0)
                j % 2 == 0 ? st_set_color(b->cells[i][j], 'r') : st_set_color(b->cells[i][j], 'b');
            else
                j % 2 == 0 ? st_set_color(b->cells[i][j], 'b') : st_set_color(b->cells[i][j], 'r');
        }
    }
}

/*  Essa funcao serve apenas para tratar eventuais erros de alocacao durante a criacao do tabuleiro,
    desfazendo todas as alocacoes anteriores a que gerou erro.
*/

void destroyBoardPartial(Board *board, int rows_filled, int cols_filled)
{
    for (int i = 0; i < rows_filled; i++)
    {
        for (int j = 0; i < cols_filled; j++)
            free_stack(board->cells[i][j]);
    }
}

void destroyBoard(Board *b)
{
    for (int i = 0; i < b->rows; i++)
    {
        for (int j = 0; j < b->cols; j++)
            free_stack(b->cells[i][j]);
        free(b->cells[i]);
    }
    free(b->cells);
}

void showBoard(Board *b)
{
    printf("    ");
    for (int j = 0; j < b->cols; j++)
        printf(" %zu  ", j + 1);
    printf("\n");

    printf(ORANGE "   +" RESET);
    for (int j = 0; j < b->cols; j++)
        printf(ORANGE "---+" RESET);
    printf("\n");

    for (int i = 0; i < b->rows; i++)
    {
        printf(" %zu", i + 1);
        printf(ORANGE " |" RESET);

        for (int j = 0; j < b->cols; j++)
        {
            char color = st_view_color(b->cells[i][j]);
            color == 'r' ? printf(RED " %c" RESET, TOKEN) : printf(BLUE " %c" RESET, TOKEN);
            printf(ORANGE " |" RESET);
        }
        printf("\n");

        printf(ORANGE "   +" RESET);
        for (int j = 0; j < b->rows; j++)
            printf(ORANGE "---+" RESET);
        printf("\n");
    }
}

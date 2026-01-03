#include "../include/board.h"
#include "../include/hand.h"
#include <stdio.h>
#include <stdlib.h>

Board *createBoard(int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
        return NULL;

    Board *new_board = (Board *)malloc(sizeof(Board));

    if (!new_board)
        return NULL;

    new_board->rows = rows;
    new_board->cols = cols;

    new_board->cells = (stack ***)malloc(rows * sizeof(stack **));
    if (!new_board->cells)
        return NULL;

    for (int i = 0; i < rows; i++)
    {
        new_board->cells[i] = (stack **)malloc(cols * sizeof(stack *));
        if (!new_board->cells[i])
        {
            destroyBoardPartial(new_board, i, cols);
            return NULL;
        }

        for (int j = 0; j < cols; j++)
        {
            new_board->cells[i][j] = create_stack();
            if (!new_board->cells[i][j])
            {
                destroyBoardPartial(new_board, i + 1, j);
                return NULL;
            }
        }
    }
    return new_board;
}

int initBoard(Board *b)
{
    if (!b)
        return -1;

    for (int i = 0; i < b->rows; i++)
    {
        for (int j = 0; j < b->cols; j++)
        {
            insert_stack(b->cells[i][j], 'O');

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

int destroyBoardPartial(Board *b, int rows_filled, int cols_filled)
{
    if (!b)
        return -1;

    for (int i = 0; i < rows_filled; i++)
    {
        for (int j = 0; j < cols_filled; j++)
            free_stack(b->cells[i][j]);
    }

    return 0;
}

int destroyBoard(Board *b)
{
    if (!b)
        return -1;

    for (int i = 0; i < b->rows; i++)
    {
        for (int j = 0; j < b->cols; j++)
            free_stack(b->cells[i][j]);
        free(b->cells[i]);
    }
    free(b->cells);

    return 0;
}

int showBoard(Board *b)
{
    if (!b)
        return -1;

    printf("    ");
    for (int j = 0; j < b->cols; j++)
        printf(" %zu  ", j + 1);
    printf("\n");

    printf(BLACK "   +" RESET);
    for (int j = 0; j < b->cols; j++)
        printf(BLACK "---+" RESET);
    printf("\n");

    for (int i = 0; i < b->rows; i++)
    {
        printf(" %zu", i + 1);
        printf(BLACK " |" RESET);

        for (int j = 0; j < b->cols; j++)
        {
            char color = st_view_color(b->cells[i][j]);
            if (st_view_size(b->cells[i][j]))
            {
                color == 'r' ? printf(RED " %d" RESET, st_view_size(b->cells[i][j]))
                             : printf(BLUE " %d" RESET, st_view_size(b->cells[i][j]));
            }
            else
            {
                color == 'r' ? printf(RED " %c" RESET, TOKEN) : printf(BLUE " %c" RESET, TOKEN);
            }
            printf(BLACK " |" RESET);
        }
        printf("\n");

        printf(BLACK "   +" RESET);
        for (int j = 0; j < b->rows; j++)
            printf(BLACK "---+" RESET);
        printf("\n");
    }

    return 0;
}

int fillBoard(Board *b)
{
    if (!b)
        return -1;

    for (int i = 0; i < b->rows; i++)
    {
        for (int j = 0; j < b->cols; j++)
        {
            insert_stack(b->cells[i][j], 'O');
        }
    }

    return 1;
}

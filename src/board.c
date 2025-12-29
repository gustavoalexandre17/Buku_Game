#include "board.h"
#include <stdio.h>
#include <stdlib.h>

/*Faltando pensar em uma melhor maneira de tratar possiveis erros de alocacao*/

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

void initBoard(Board b)
{
    for (int i = 0; i < b.rows; i++)
    {
        for (int j = 0; j < b.cols; j++)
        {
            insert_stack(b.cells[i][j], WHITE);
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
        printf(" %zu  ", j);
    printf("\n");

    printf("   +");
    for (int j = 0; j < b->cols; j++)
        printf("---+");
    printf("\n");

    for (int i = 0; i < b->rows; i++)
    {
        printf(" %zu |", i);

        for (int j = 0; j < b->cols; j++)
        {
            char c = view_top(b->cells[i][j]);
            printf(" %c |", c);
        }
        printf("\n");

        printf("   +");
        for (int j = 0; j < b->rows; j++)
            printf("---+");
        printf("\n");
    }
}
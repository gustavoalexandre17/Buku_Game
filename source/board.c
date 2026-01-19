#include "../include/board.h"
#include <stdio.h>
#include <stdlib.h>

/*Passievel de refatoracao*/
Board *create_board()
{
    int rows, cols;

    printf("\nDigite o numero de linhas e colunas do seu tabuleiro:\n");
    printf("\nO numero de linhas e colunas devem ambos pares e iguais!\n");
    scanf("%d%d", &rows, &cols);

    while (rows != cols || rows <= 0 || cols <= 0 || rows >= 10 || cols >= 10 || rows % 2 != 0 || cols % 2 != 0)
    {
        printf("\nInsira dimensoes validas!\n");
        scanf("%d %d", &rows, &cols);
    }

    if (rows <= 0 || cols <= 0)
        return NULL;

    Board *new_board = (Board *)malloc(sizeof(Board));

    if (!new_board)
        return NULL;

    new_board->rows = rows;
    new_board->cols = cols;
    new_board->cells = (Stack ***)malloc(rows * sizeof(Stack **));

    if (!new_board->cells)
        return NULL;

    for (int i = 0; i < rows; i++)
    {
        new_board->cells[i] = (Stack **)malloc(cols * sizeof(Stack *));
        if (!new_board->cells[i])
        {
            destroy_board_partial(new_board, i, cols);
            return NULL;
        }

        for (int j = 0; j < cols; j++)
        {
            new_board->cells[i][j] = create_stack();
            if (!new_board->cells[i][j])
            {
                destroy_board_partial(new_board, i + 1, j);
                return NULL;
            }
        }
    }
    printf("\nTabuleiro criado com sucesso!\n");
    return new_board;
}

int init_board(Board *b)
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
    return 0;
}

/*  Essa funcao serve apenas para tratar eventuais erros de alocacao durante a criacao do tabuleiro,
    desfazendo todas as alocacoes anteriores a que gerou erro.
*/

int destroy_board_partial(Board *b, int rows_filled, int cols_filled)
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

int destroy_board(Board *b)
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

int show_board(Board *b)
{
    if (!b)
        return -1;

    printf("    ");
    for (int j = 0; j < b->cols; j++)
        printf(" %d  ", j + 1);
    printf("\n");

    printf(WHITE "   +" RESET);
    for (int j = 0; j < b->cols; j++)
        printf(WHITE "---+" RESET);
    printf("\n");

    for (int i = 0; i < b->rows; i++)
    {
        printf(" %d", i + 1);
        printf(WHITE " |" RESET);

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
            printf(WHITE " |" RESET);
        }
        printf("\n");

        printf(WHITE "   +" RESET);
        for (int j = 0; j < b->rows; j++)
            printf(WHITE "---+" RESET);
        printf("\n");
    }

    return 0;
}

int fill_board(Board *b)
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

int view_board_size(Board *b) { return b->rows; }

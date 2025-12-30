#include "../include/hand.h"
#include "../include/board.h"
#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>

Hand createHand()
{
    Hand newHand;

    newHand.pieces = create_stack();

    return newHand;
}

int pick_row(Hand *hand, Board *board, int row, int tamanho)
{
    if (hand == NULL && board == NULL)
    {
        return 0;
    }

    for (int i = 0; i < tamanho; i++)
    {
        while (view_size(board->cells[row][i]) > 1)
        {
            insert_stack(hand->pieces, 'O');
            pop_stack(board->cells[row][i]);
        }
    }

    return 1;
}

int pick_col(Hand *hand, Board *board, int col, int tamanho)
{
    if (hand == NULL && board == NULL)
    {
        return 0;
    }

    for (int i = 0; i < tamanho; i++)
    {
        while (view_size(board->cells[i][col]) > 1)
        {
            insert_stack(hand->pieces, 'O');
            pop_stack(board->cells[i][col]);
        }
    }

    return 1;
}

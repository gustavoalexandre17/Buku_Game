#include "../include/hand.h"
#include "../include/board.h"
#include "../include/stack.h"
#include <stdlib.h>

Hand *createHand()
{
    Hand *newHand = (Hand *)malloc(sizeof(Hand));
    newHand->pieces = create_stack();
    return newHand;
}

int pick_row(Hand *hand, Board *board, int row, int size)
{
    if (!hand || !board)
        return -1;

    for (int i = 0; i < size; i++)
    {
        while (st_view_size(board->cells[row][i]) > 1)
        {
            insert_stack(hand->pieces, 'O');
            pop_stack(board->cells[row][i]);
        }
    }
    return 0;
}

int pick_col(Hand *hand, Board *board, int col, int size)
{
    if (!hand || !board)
        return -1;

    for (int i = 0; i < size; i++)
    {
        while (st_view_size(board->cells[i][col]) > 1)
        {
            insert_stack(hand->pieces, 'O');
            pop_stack(board->cells[i][col]);
        }
    }
    return 0;
}

int hand_size(Hand *hand) { return st_view_size(hand->pieces); }

int free_hand(Hand *hand)
{
    if (!hand)
        return -1;

    free_stack(hand->pieces);
    free(hand);

    return 0;
}
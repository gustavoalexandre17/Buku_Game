#ifndef HAND_H
#define HAND_H

#include "board.h"

typedef struct
{
    stack *pieces;
} Hand;

Hand *createHand();
int pick_row(Hand *hand, Board *board, int row, int size);
int pick_col(Hand *hand, Board *board, int col, int size);
int hand_size(Hand *hand);
int free_hand(Hand *hand);

#endif
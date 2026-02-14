#ifndef HAND_H
#define HAND_H

#include "../move.h"
#include "board.h"

typedef struct {
    Stack *pieces;
} Hand;

Hand *create_hand(int board_size);
int pick_row(Hand *hand, Board *board, int row, int size);
int pick_col(Hand *hand, Board *board, int col, int size);
int put_hand(Hand *hand, Board *board, PlayedHand *ph);
int hand_size(Hand *hand);
int free_hand(Hand *hand);

#endif

#include "board.h"
#include "stack.h"

typedef struct
{
    stack *pieces;
} Hand;

Hand createHand();
int pick_row(Hand *hand, Board *board, int row, int tamanho);
int pick_col(Hand *hand, Board *board, int col, int tamanho);
void free_hand(Hand *hand);

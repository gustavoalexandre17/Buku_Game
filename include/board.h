#ifndef BOARD_H
#define BOARD_H

#include "colors.h"
#include "stack.h"
#define TOKEN 'x'

typedef struct
{
    int rows;
    int cols;
    stack ***cells;
} Board;

Board *createBoard(int rows, int cols);
int destroyBoardPartial(Board *b, int rows_filled, int cols_filled);
int initBoard(Board *b);
int fillBoard(Board *b);
int showBoard(Board *b);
int destroyBoard(Board *b);

#endif

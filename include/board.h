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

Board createBoard(int rows, int cols);
void destroyBoardPartial(Board *board, int rows_filled, int cols_filled);
void initBoard(Board *b);
void showBoard(Board *b);
void destroyBoard(Board *b);

#endif

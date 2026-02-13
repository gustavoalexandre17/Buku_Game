#ifndef BOARD_H
#define BOARD_H

#include "colors.h"
#include "stack.h"
#define TOKEN 'x'

typedef struct {
    int rows;
    int cols;
    int turns;
    Stack ***cells;
} Board;

Board *create_board(int rows, int cols);
int destroy_board(Board *b);
int destroy_board_partial(Board *b, int rows_filled, int cols_filled);
int init_board(Board *b);
int fill_board(Board *b);
int show_board(Board *b);
int view_board_size(Board *b);

#endif

#ifndef INPUT_H
#define INPUT_H

#include "../move.h"

int input_get_board_dimensions(int *rows, int *cols);
int input_select_row(int max_rows);
int input_select_col(int max_cols);
PlayedHand *input_get_played_positions(int hand_size);

#endif

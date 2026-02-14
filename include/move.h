#ifndef MOVE_H
#define MOVE_H

typedef struct
{
    int row;
    int col;
    int size;
} PlayedHand;

PlayedHand *create_played_hand(int size);
int validate_full_move(PlayedHand *ph, int boardSize);
int validate_parcial_move(int row, int col, int boardSize);
int is_neighbor(PlayedHand ph, int row, int col);
int already_played(int row, int col, int index, PlayedHand *ph);
void free_played_hand(PlayedHand *ph);

#endif
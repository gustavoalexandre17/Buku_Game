#ifndef MAKEMOVE_H
#define MAKEMOVE_H

typedef struct
{
    int row;
    int col;
    int size;
} playedHand;

playedHand *createPlayedHand(int size);
int validateTotalMove(playedHand *ph, int boardSize);
int validateParcialMove(int row, int col, int boardSize);
int isNeighbor(playedHand ph, int row, int col);
int isAlreadyPlayed(int row, int col, int index, playedHand *ph);
void freePlayedHand(playedHand *ph);

#endif

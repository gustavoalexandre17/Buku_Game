#ifndef MAKEMOVE_H
#define MAKEMOVE_H

typedef struct
{
    int row;
    int col;
} playedHand;

playedHand *createPlayedHand(int size);
void freePlayedHand(playedHand *ph);

#endif

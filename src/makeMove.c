#include "../include/makeMove.h"
#include <stdio.h>
#include <stdlib.h>

playedHand *createPlayedHand(int size)
{
    playedHand *newPlayedHand = (playedHand *)malloc(size * sizeof(playedHand));

    if (!newPlayedHand)
        return NULL;

    return newPlayedHand;
}

void freePlayedHand(playedHand *ph) { free(ph); }

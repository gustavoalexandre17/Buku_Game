#include "../include/move.h"
#include <stdlib.h>

PlayedHand *create_played_hand(int size) {
    PlayedHand *newPH = (PlayedHand *)malloc(size * sizeof(PlayedHand));

    if (!newPH)
        return NULL;

    newPH->size = size;

    return newPH;
}

void free_played_hand(PlayedHand *ph) { free(ph); }

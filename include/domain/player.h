#ifndef PLAYER_H
#define PLAYER_H

#include "stack.h"

typedef struct {
    Stack *points;
    char *color;
} Player;

Player *create_player(char *color);

#endif
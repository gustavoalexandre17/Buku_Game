#ifndef PLAYER_H
#define PLAYER_H

#include "../include/stack.h"

typedef struct
{
    stack *points;
    char *color;
} Player;

Player *create_player(char *color);

#endif
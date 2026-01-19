#include "../include/player.h"
#include "../include/stack.h"
#include <stdlib.h>

Player *create_player(char *color) {
    Player *new_player = (Player *)malloc(sizeof(Player));
    if (!new_player)
        return NULL;

    new_player->points = create_stack();
    if (!new_player->points)
        return NULL;

    new_player->color = color;

    return new_player;
}
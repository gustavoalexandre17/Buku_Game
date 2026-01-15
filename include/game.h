#ifndef GAME_H
#define GAME_H

#include "../include/board.h"
#include "../include/hand.h"
#include "../include/move.h"
#include "../include/player.h"

void game_round(Board *board, Hand *hand, Player *player);
int insert_points(Board *board, PlayedHand *play, Player *player);

#endif

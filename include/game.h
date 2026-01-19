#ifndef GAME_H
#define GAME_H

#include "../include/board.h"
#include "../include/hand.h"
#include "../include/move.h"
#include "../include/player.h"

void game_round(Board *board, Hand *hand, Player *player);
int check_points(Board *board, Player *player1, Player *player2);

#endif

#ifndef GAME_H
#define GAME_H

#include "../include/board.h"
#include "../include/hand.h"
#include "../include/move.h"
#include "../include/player.h"

int game_round(Board *board, Hand *hand, Player *player);
int check_points(Board *board, Player *player);
void withdrawal(Board *board, Player *winner);
void singletonsEndGame(Board *board, Player *p1, Player *p2);

#endif

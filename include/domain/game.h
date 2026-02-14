#ifndef GAME_H
#define GAME_H

#include "domain/board.h"
#include "domain/hand.h"
#include "domain/player.h"
#include "move.h"

int game_round(Board *board, Hand *hand, Player *player);
int check_points(Board *board, Player *player);
void withdrawal(Board *board, Player *winner);
void singletonsEndGame(Board *board, Player *p1, Player *p2);

#endif

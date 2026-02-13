#ifdef DISPLAY_H
#DEFINE DISPLAY_H

void display_board(Board *b);
void display_turn_start(Player* player);
void display_hand_size(int size);
void display_move_valid();
void display_current_score(Player* p1, Player* p2);
void display_game_end_points(Player *winner, int points)
void display_game_end_singletons(Player *winner, int points)
void display_game_end_withdrawal(Player *winner, int points)
void display_goodbye()
void display_played_move(PlayedHand *move, int size);


#endif
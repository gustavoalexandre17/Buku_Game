#ifdef GAMELOGIC_H
#define GAMELOGIC_H

typedef enum {
    GAME_CONTINUES,
    WIN_BY_POINTS,
    WIN_BY_SINGLETONS,
    WIN_BY_WITHDRAWAL
} GameEndReason;

typedef struct {
    int game_over;
    GameEndReason reason;
    Player *winner;
    int points;
} GameResult;

typedef struct {
    bool is_valid;
    char message[50]
} ValidationResult;

bool check_all_ingletons(Board *board);
int calculate_and_collect_points(Board *board, Player *player)
bool has_won_by_points(Board* board, Player* player);

#endif
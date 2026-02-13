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
int calculate_and_collect_points(Board *board, Player *player);
bool has_won_by_points(Board* board, Player* player);
Player *determine_winner(Player *p1, Player *p2);
ValidationResult validate_move(Board* board, PlayedHand* move, int move_size);
int validate_parcial_move(int row, int col, int boardSize);
int is_neighbor(PlayedHand ph, int row, int col);
int already_played(int row, int col, int index, PlayedHand *ph);

#endif
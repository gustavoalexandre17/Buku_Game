#ifdef GAMELOGIC_H
#define GAMELOGIC_H

typedef enum {
    GAME_CONTINUES,
    WIN_BY_POINTS,
    WIN_BY_SINGLETONS,
    WIN_BY_WITHDRAWAL
} GameEndReason;

typedef struct {
    bool game_over;
    GameEndReason reason;
    Player *winner;
    int points;
} GameResult;

typedef struct {
    bool is_valid;
    char message[50]
} ValidationResult;

#endif
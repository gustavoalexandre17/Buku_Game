#include "domain/board.h"
#include "domain/player.h"
#include <stdbool.h>

bool check_all_ingletons(Board *board) {
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            Stack *cell = board->cells[i][j];
            int value = st_view_size(cell);

            if (value != 1)
                return 0;
        }
    }
    return 1;
}

int calculate_and_collect_points(Board *board, Player *player) {
    if (!board || !player)
        return -1;

    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            Stack *cell = board->cells[i][j];
            int value = st_view_size(cell);

            if (st_view_color(cell) == player->color[0]) {
                if (value >= 3) {
                    for (int k = 0; k < value; k++) {
                        pop_stack(cell);
                        insert_stack(player->points, 'O');
                    }
                }
            }
        }
    }
    return st_view_size(player->points);
}

bool has_won_by_points(Board* board, Player* player) {
    int points = st_view_size(player->points);
    int totalCells = board->rows * board->cols;
    return points > (totalCells / 2);
}

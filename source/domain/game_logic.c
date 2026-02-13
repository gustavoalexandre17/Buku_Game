#include "domain/game_logic.h"

bool check_all_singletons(Board *board) {
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

Player *determine_winner(Player *p1, Player *p2) {
    return (st_view_size(p1->points) > st_view_size(p2->points)) ? p1 : p2;
}

// Refatoracao urgente
ValidationResult validate_move(PlayedHand *ph, int boardSize) {
    ValidationResult result;
    result.is_valid = true;
    result.message[0] = "";

    if (!ph) {
        result.is_valid = false;
        return result;
    }

    for (int i = 0; i < ph->size; i++) {
        if (!validate_parcial_move(ph[i].row, ph[i].col, boardSize)) {
            result.is_valid = false;
            return result;
        }

        else if (i != 0) {
            int totalNeighbor = 4;
            int Neighbors[4][2] = {{ph[i - 1].row, ph[i - 1].col + 1},
                                   {ph[i - 1].row, ph[i - 1].col - 1},
                                   {ph[i - 1].row + 1, ph[i - 1].col},
                                   {ph[i - 1].row - 1, ph[i - 1].col}};

            // Verificar se é vizinho

            int test = 0;
            test += is_neighbor(ph[i], Neighbors[0][0], Neighbors[0][1]);
            test += is_neighbor(ph[i], Neighbors[1][0], Neighbors[1][1]);
            test += is_neighbor(ph[i], Neighbors[2][0], Neighbors[2][1]);
            test += is_neighbor(ph[i], Neighbors[3][0], Neighbors[3][1]);

            if (test == 1) {
                Neighbors[0][0] = ph[i].row;
                Neighbors[0][1] = ph[i].col + 1;

                Neighbors[1][0] = ph[i].row;
                Neighbors[1][1] = ph[i].col - 1;

                Neighbors[2][0] = ph[i].row + 1;
                Neighbors[2][1] = ph[i].col;

                Neighbors[3][0] = ph[i].row - 1;
                Neighbors[3][1] = ph[i].col;

                for (int j = 0; j < 4; j++)
                    if (!validate_parcial_move(Neighbors[j][0], Neighbors[j][1], boardSize) ||
                        already_played(Neighbors[j][0], Neighbors[j][1], i, ph))
                        totalNeighbor--;
            } else {
                result.is_valid = false;
                return result;
            }

            if (totalNeighbor == 0) {
                result.is_valid = false;
                return result;
            }
        }
    }
    return result;
}

int validate_parcial_move(int row, int col, int boardSize) {
    if (col < 0 || row < 0 || col > boardSize || row > boardSize)
        return 0;

    return 1;
}

int is_neighbor(PlayedHand ph, int row, int col) {
    if (ph.row == row && ph.col == col)
        return 1;

    return 0;
}

int already_played(int row, int col, int index, PlayedHand *ph) {
    for (int i = 0; i < index; i++) {
        if (row == ph[i].row && col == ph[i].col)
            return 1;
    }
    return 0;
}

GameResult execute_round(Board *board, Hand *hand, PlayedHand *move, int move_size, Player *player) {
    GameResult result;

    ValidationResult validation = validate_move(move, board->rows);
    if (!validation.is_valid) {
        result.game_over = false;
        return result;
    }

    put_hand(hand, board, move);

    calculate_and_collect_points(board, player);

    if (has_won_by_points(board, player)) {
        result.game_over = true;
        result.reason = WIN_BY_POINTS;
        result.winner = player;
        result.points = st_view_size(player->points);
    }
    return (GameResult){.game_over = false};
}

GameResult resolve_singletons_end(Board* board, Player* p1, Player* p2) {
    GameResult result;
    if (check_all_ingletons(board)) {
        result.game_over = true;
        result.reason = WIN_BY_SINGLETONS;
        result.winner = determine_winner(p1, p2);
        result.points = st_view_size(result.winner->points);
    } else {
        result.game_over = false;
    }
    return result;
}

GameResult resolve_withdrawal(Board* board, Player* winner) {
    GameResult result;

    if (check_all_singletons(board)) {
        result.game_over = true;
        result.reason = WIN_BY_SINGLETONS;
        result.winner = winner;
        result.points = st_view_size(winner->points);
    }

    result.game_over = false;

    return result;
}

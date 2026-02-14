#include "domain/board.h"
#include "domain/hand.h"
#include "ui/input.h"
#include "domain/game.h"
#include "domain/player.h"
#include "domain/game_logic.h"

#include <stdio.h>
#include <stdbool.h>

int main() {
    int rows, cols;

    input_get_board_dimensions(&rows, &cols);

    Board *board = create_board(rows, cols);
    Hand *hand = create_hand(view_board_size(board));

    Player *p1 = create_player("vermelho");
    Player *p2 = create_player("azul");

    init_board(board);

    system("clear");
    display_board(board);

    Player *current = p1;
    Player *other = p2;

    while (true) {

        if (board->turns > 1 && check_all_singletons(board)) {
            GameResult result = resolve_singletons_endgame(board, p1, p2);
            display_game_end_singletons(result.winner, result.points);
        }

        display_turn_start(current);

        bool is_p1 = current == p1;
        int selected = is_p1 ? input_select_row(board->rows) : input_select_col(board->cols);

        if (is_p1) {
            pick_row(hand, board, selected, board->cols);
        } else {
            pick_col(hand, board, selected, board->rows);
        }

        system("clear");
        display_board(board);

        int hand_sz = hand_size(hand);

        // TODO: resolve_withdrawal
        if (check_withdrawal(hand)) {
            GameResult result = resolve_withdrawal(board, other);
            display_game_end_withdrawal(result.winner, result.points);
        }

        display_hand_size(hand_sz);

        PlayedHand *move = input_get_played_positions(hand_sz);        

        ValidationResult validation;
        do {
            validation = validate_move(hand, board->cells);
            if (!validation.is_valid) {
                printf("Movimento invalido!\n");
                free_played_hand(move);
                move = input_get_played_positions(hand_sz);
            }
        } while (!validation.is_valid);

        GameResult result = execute_round(board, hand, move, hand_sz, current);

        system("clear");
        display_board(board);
        display_move_valid(move, hand_sz);
        display_played_move(move, hand_sz);

        if (result.game_over) {
            display_game_end_points(result.winner, result.points);
            break;
        }

        display_current_score(p1, p2);

        free_played_hand(move);
        board->turns++;
    }

    destroy_board(board);
    free_hand(hand);
    display_goodbye();

    return 0;
}
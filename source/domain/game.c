#include "domain/game.h"
#include "domain/board.h"
#include "domain/hand.h"
#include "../include/move.h"
#include "domain/player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_points(Board *board, Player *player) {
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
    int half_points = (board->rows * board->cols) / 2;
    if (st_view_size(player->points) > half_points) {
        return 1;
        display_game_end_points(player, st_view_size(player->points));
    }
    return 0;
}

int allSingletons(Board *board) {
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

Player *get_winner(Player *p1, Player *p2) {
    Player *winner;

    if (st_view_size(p1->points) > st_view_size(p2->points))
        winner = p1;
    else
        winner = p2;

    return winner;
}

void singletonsEndGame(Board *board, Player *p1, Player *p2) {
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            Stack *cell = board->cells[i][j];
            int value = st_view_size(cell);

            for (int k = 0; k < value; k++) {
                pop_stack(cell);
                st_view_color(cell) == 'v' ? insert_stack(p1->points, 'O') : insert_stack(p2->points, 'O');
            }
        }
    }
    Player *winner = get_winner(p1, p2);
    display_game_end_singletons(winner, st_view_size(winner->points));
}

void withdrawal(Board *board, Player *winner) {
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            Stack *cell = board->cells[i][j];
            int value = st_view_size(cell);

            for (int k = 0; k < value; k++) {
                pop_stack(cell);
                insert_stack(winner->points, 'O');
            }
        }
    }
    system("clear");
    show_board(board);
    display_game_end_withdrawal(winner, st_view_size(winner->points));
}

int game_round(Board *board, Hand *hand, Player *player) {
    int row = board->rows;
    int col = board->cols;
    int playedRow, playedCol;

    // fim de jogo por singletons
    if (board->turns > 1 && allSingletons(board))
        return 1;

    printf("\nVez do jogador %s:\n", player->color);

    if (!strcmp(player->color, "vermelho")) {
        printf("Selecione a linha (1 a %d):\n", row);
        scanf("%d", &playedRow);

        while (playedRow < 1 || playedRow > row) {
            printf("Linha invalida, por favor, digite uma linha valida!\n");
            scanf("%d", &playedRow);
        }

        pick_row(hand, board, playedRow - 1, board->cols);
    }

    else if (!strcmp(player->color, "azul")) {
        printf("Selecione a coluna (1 a %d):\n", col);
        scanf("%d", &playedCol);

        while (playedCol < 1 || playedCol > row) {
            printf("Coluna invalida, por favor, digite uma coluna valida!\n");
            scanf("%d", &playedCol);
        }

        pick_col(hand, board, playedCol - 1, board->cols);
    }

    printf("\nEstado atual:\n");
    system("clear");
    display_board(board);

    int size = hand_size(hand);

    // fim de jogo por desistencia
    if (size == 0)
        return 2;

    display_hand_size(size);
    PlayedHand *play = create_played_hand(size);

    input_get_played_positions(size);
    // validate_played_positions(play, size, board);

    /*TODO: 
    Ajustar essa verificacao para se encaxar no played positions 
            valid = validate_full_move(play, row);
            system("clear");
            show_board(board);*/

    put_hand(hand, board, play);
    int gameOver = check_points(board, player);
    // fim de jogo por pontos
    if (gameOver == 1)
        return 3;

    system("clear");
    display_board(board);

    display_played_move(play, size);

    printf("\n");
    free_played_hand(play);
    board->turns++;

    return 0;
}
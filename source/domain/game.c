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
        printf("Fim de jogo por pontuacao, o jogador %s ganhou com %d pontos!\n", player->color, st_view_size(player->points));
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
    printf("Fim de jogo por singlestons, o jogador %s ganhou com %d pontos!\n", winner->color, st_view_size(winner->points));
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
    int points = st_view_size(winner->points);
    printf("Fim de jogo por desistencia, o jogador %s ganhou com %d pontos!\n", winner->color, points);
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
    show_board(board);

    int size = hand_size(hand);

    // fim de jogo por desistencia
    if (size == 0)
        return 2;

    printf("\nO tamanho da mao e de: %d\n", hand_size(hand));
    PlayedHand *play = create_played_hand(size);

    int valid = -1;
    while (valid == -1) {
        for (int i = 0; i < hand_size(hand); i++) {
            int tempRow, tempCol;
            printf("\nDigite a linha da %d° jogada: ", i + 1);
            scanf("%d", &tempRow);

            printf("Digite a coluna da %d° jogada: ", i + 1);
            scanf("%d", &tempCol);

            play[i].row = tempRow - 1;
            play[i].col = tempCol - 1;

            valid = validate_full_move(play, row);
            system("clear");
            show_board(board);
        }
    }

    printf("\nJogada válida\n");
    put_hand(hand, board, play);
    int gameOver = check_points(board, player);
    // fim de jogo por pontos
    if (gameOver == 1)
        return 3;

    system("clear");
    show_board(board);

    printf("Jogada realizada -> ");
    for (int i = 0; i < size; i++)
        printf("{%d,%d} ", play[i].row, play[i].col);

    printf("\n");
    free_played_hand(play);
    board->turns++;

    // continua normalmente
    return 0;
}
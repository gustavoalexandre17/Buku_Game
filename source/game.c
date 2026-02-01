#include "../include/game.h"
#include "../include/board.h"
#include "../include/hand.h"
#include "../include/move.h"
#include "../include/player.h"
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
        printf("Fim de jogo por pontuacao, o jogador %s ganhou com %d pontos!\n", player->color,
               st_view_size(player->points));
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
    printf("Fim de jogo por singlestons, o jogador %s ganhou com %d pontos!\n", winner->color, winner->points);
}

void withdrawal(Board *board, Player *winner, Colors *colors) {
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
    show_board(board, colors);
    int points = st_view_size(winner->points);
    printf("Fim de jogo por desistencia, o jogador %s ganhou com %d pontos!\n", winner->color, points);
}

int game_round(Board *board, Hand *hand, Player *player, Colors *colors) {
    int row = board->rows;
    int col = board->cols;
    int playedRow, playedCol;

    // fim de jogo por singletons
    if (board->turns > 1 && allSingletons(board))
        return 1;

    printf("\nVez do jogador %s:\n", player->color);

    if (!strcmp(player->color, colors->colorLightSquares)) {
        printf("Selecione a linha (1 a %d):\n", row);
        scanf("%d", &playedRow);

        while (playedRow < 1 || playedRow > row) {
            printf("Linha invalida, por favor, digite uma linha valida!\n");
            scanf("%d", &playedRow);
        }

        pick_row(hand, board, playedRow - 1, board->cols);
    }

    else if (!strcmp(player->color, colors->colorDarkSquares)) {
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
    show_board(board, colors);

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

            valid = validate_full_move(play, row, i + 1);
            system("clear");
            show_board(board, colors);
        }
    }

    printf("\nJogada válida\n");
    put_hand(hand, board, play);
    int gameOver = check_points(board, player);
    // fim de jogo por pontos
    if (gameOver == 1)
        return 3;

    system("clear");
    show_board(board, colors);

    printf("Jogada realizada -> ");
    for (int i = 0; i < size; i++)
        printf("{%d,%d} ", play[i].row + 1, play[i].col + 1);

    printf("\n");
    free_played_hand(play);
    board->turns++;

    // continua normalmente
    return 0;
}

int choose_colors(Colors *colors) {
    if (!colors)
        return 0;

    char *curr = "light_squares";

    char *nameColors[] = {"branco",       "cinza", "vermelho",   "laranja",     "amarelo", "verde_claro",
                          "verde_escuro", "ciano", "azul_claro", "azul_escuro", "magenta", "rosa"};

    char *nameColorsId[] = {WHITE, GRAY, RED, ORANGE, YELLOW, LGREEN, GREEN, CYAN, LBLUE, BLUE, MAGENTA, ROSE};

    for (int i = 0; i < 3; i++) {
        int numColor;

        system("clear");

        if (strcmp(curr, "light_squares") == 0) {
            printf("Selecione a cor do primeiro jogador pelo seu id: \n");
        } else if (strcmp(curr, "dark_squares") == 0) {
            printf("Selecione a cor do segundo jogador pelo seu id: \n");
        } else if (strcmp(curr, "board") == 0) {
            printf("Selecione a cor do tabulero pelo seu id: \n");
        }

        printf(WHITE "1 - Branco\n" RESET);
        printf(GRAY "2 - Cinza\n" RESET);
        printf(RED "3 - Vermelho\n" RESET);
        printf(ORANGE "4 - Laranja\n" RESET);
        printf(YELLOW "5 - Amarelo\n" RESET);
        printf(LGREEN "6 - Verde claro\n" RESET);
        printf(GREEN "7 - Verde escuro\n" RESET);
        printf(CYAN "8 - Ciano\n" RESET);
        printf(LBLUE "9 - Azul claro\n" RESET);
        printf(BLUE "10 - Azul escuro\n" RESET);
        printf(MAGENTA "11 - Magenta\n" RESET);
        printf(ROSE "12 - Rosa\n" RESET);

        scanf("%d", &numColor);

        while (numColor < 1 || numColor > 12) {
            printf("Cor inválida, selecione um id válido");
            scanf("%d", &numColor);
        }

        if (strcmp(curr, "light_squares") == 0) {
            colors->colorLightSquares = nameColors[numColor - 1];
            colors->colorLightSquaresId = nameColorsId[numColor - 1];
            curr = "dark_squares";
        } else if (strcmp(curr, "dark_squares") == 0) {
            colors->colorDarkSquares = nameColors[numColor - 1];
            colors->colorDarkSquaresId = nameColorsId[numColor - 1];
            curr = "board";
        } else if (strcmp(curr, "board") == 0) {
            colors->colorBoard = nameColorsId[numColor - 1];
        }
    }

    return 1;
}

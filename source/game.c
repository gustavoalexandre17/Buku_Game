#include "../include/game.h"
#include "../include/board.h"
#include "../include/hand.h"
#include "../include/move.h"
#include "../include/player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// PROXIMO PASSO: FUNCAO UPDATE SCORE
int check_points(Board *board, Player *player1, Player *player2)
{
    if (!board || !player1 || !player2)
        return -1;

    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            Stack *cell = board->cells[i][j];
            int value = st_view_size(cell);

            if (value >= 3) // PROVISORIO - PARA TESTES
            {
                for (int k = 0; k < value; k++)
                {
                    pop_stack(cell);
                    st_view_color(cell) == 'r' ? insert_stack(player1->points, 'O')
                                               : insert_stack(player2->points, 'O');
                }
            }
        }
    }
    printf("Pontuacao atual do jogador %s: %d\n", player1->color, st_view_size(player1->points));
    printf("Pontuacao atual do jogador %s: %d\n", player2->color, st_view_size(player2->points));
    return 0;
}

void game_round(Board *board, Hand *hand, Player *player)
{
    int row = board->rows;
    int col = board->cols;
    int playedRow, playedCol;

    printf("\nVez do jogador %s:\n", player->color);

    if (!strcmp(player->color, "vermelho"))
    {
        printf("Selecione a linha (1 a %d):\n", row);
        scanf("%d", &playedRow);

        while (playedRow < 1 || playedRow > row)
        {
            printf("Linha invalida, por favor, digite uma linha valida!\n");
            scanf("%d", &playedRow);
        }

        pick_row(hand, board, playedRow - 1, board->cols);
    }

    else if (!strcmp(player->color, "azul"))
    {
        printf("Selecione a coluna (1 a %d):\n", col);
        scanf("%d", &playedCol);

        while (playedCol < 1 || playedCol > row)
        {
            printf("Coluna invalida, por favor, digite uma coluna valida!\n");
            scanf("%d", &playedCol);
        }

        pick_col(hand, board, playedCol - 1, board->cols);
    }

    printf("\nEstado atual:\n");
    system("clear");
    show_board(board);

    int size = hand_size(hand);

    printf("\nO tamanho da mao e de: %d\n", hand_size(hand));
    PlayedHand *play = create_played_hand(size);

    int valid = -1;
    while (valid == -1)
    {
        for (int i = 0; i < hand_size(hand); i++)
        {
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

    system("clear");
    show_board(board);

    printf("Jogada realizada -> ");
    for (int i = 0; i < size; i++)
        printf("{%d,%d} ", play[i].row, play[i].col);

    printf("\n");
    free_played_hand(play);
}
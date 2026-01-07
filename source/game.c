#include "../include/game.h"
#include "../include/board.h"
#include "../include/hand.h"
#include "../include/move.h"
#include "../include/player.h"
#include <stdio.h>
#include <string.h>

// PROXIMO PASSO: FUNCAO UPDATE SCORE

void game_round(Board *board, Hand *hand, PlayedHand *play, Player *player)
{
    int row = board->rows;
    int col = board->cols;
    int playedRow, playedCol;

    printf("Vez do jogador %s:\n", player->color);

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
    show_board(board);

    printf("\nO tamanho da mao e de: %d\n", hand_size(hand));
    play = create_played_hand(hand_size(hand));

    int tamanho = hand_size(hand);

    do
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
        }
    } while (validate_full_move(play, row) != 1);

    printf("\nJogada válida\n");
    put_hand(hand, board, play);
    show_board(board);

    for (int i = 0; i < tamanho; i++)
        printf("{%d,%d} ", play[i].row, play[i].col);

    printf("\n");
}

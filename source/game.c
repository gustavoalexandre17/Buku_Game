#include "../include/game.h"
#include "../include/board.h"
#include "../include/hand.h"
#include "../include/move.h"
#include "../include/player.h"
#include <stdio.h>
#include <string.h>

// PROXIMO PASSO: FUNCAO UPDATE SCORE

int insert_points(Board *board, PlayedHand *play, Player *player)
{
    if (!board || !play || !player)
        return -1;

    for (int i = 0; i < play->size; i++)
    {
        Stack *cell = board->cells[play[i].row][play[i].col];
        int value = st_view_size(cell);

        if (st_view_color(cell) == player->color[0]) // PEQUENA GAMBIARRA
            if (value == 3 || value == 4)
            {
                for (int j = 0; j < value; j++)
                {
                    pop_stack(cell);
                    insert_stack(player->points, 'O');
                }
            }
    }
    return 1;
}

/* FALTA IMPLEMENTAR A PONTUACAO */
void game_round(Board *board, Hand *hand, Player *player)
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

    int size = hand_size(hand);

    printf("\nO tamanho da mao e de: %d\n", hand_size(hand));
    PlayedHand *play = create_played_hand(size);

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
    insert_points(board, play, player);

    show_board(board);

    for (int i = 0; i < size; i++)
        printf("{%d,%d} ", play[i].row, play[i].col);

    printf("Pontuacao atual do jogador %s: %d\n", player->color, st_view_size(player->points));
    printf("\n");

    free_played_hand(play);
}

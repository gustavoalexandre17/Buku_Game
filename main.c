#include "domain/board.h"
#include "domain/hand.h"
#include "ui/input.h"
#include "domain/game.h"
#include "domain/player.h"


#include <stdio.h>

int main() {
    int rows = 0;
    int cols = 0;

    input_get_board_dimensions(&rows, &cols);

    Board *board = create_board(rows, cols);
    Hand *hand = create_hand(view_board_size(board));

    Player *p1 = create_player("vermelho");
    Player *p2 = create_player("azul");

    init_board(board);
    show_board(board);

    while (1) {
        int first_play = game_round(board, hand, p1);

        if (first_play == 1) {
            // fim de jogo por singletons
            singletonsEndGame(board, p1, p2);
            break;
        }

        else if (first_play == 2) {
            // desistencia
            withdrawal(board, p2);
            break;
        }

        else if (first_play == 3) {
            // gameover padrao
            break;
        }

        // continua o jogo
        printf("Pontuacao atual dos jogadores:\n %s: %d\n %s : %d\n", p1->color, st_view_size(p1->points), p2->color,
               st_view_size(p2->points));

        int second_play = game_round(board, hand, p2);

        if (second_play == 1) {
            // fim de jogo por singletons
            singletonsEndGame(board, p1, p2);
            break;
        }

        else if (second_play == 2) {
            // desistencia
            withdrawal(board, p2);
            break;
        }

        else if (second_play == 3) {
            // gameover padrao
            break;
        }

        printf("Pontuacao atual dos jogadores:\n %s: %d\n %s : %d\n", p1->color, st_view_size(p1->points), p2->color,
               st_view_size(p2->points));
    }

    destroy_board(board);
    free_hand(hand);
    printf("\nTabuleiro excluido com sucesso, obrigado por jogar!\n");

    return 0;
}
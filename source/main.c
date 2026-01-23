#include "../include/board.h"
#include "../include/game.h"
#include "../include/hand.h"
#include "../include/player.h"
#include <stdio.h>

int main() {
    Board *board = create_board();
    Hand *hand = create_hand(view_board_size(board));

    Player *p1 = create_player("vermelho");
    Player *p2 = create_player("azul");

    init_board(board);
    show_board(board);

    while (1) {
        int first_play = game_round(board, hand, p1);

        if (first_play == 1)
            // desistencia
            withdrawal(board, p2);

        else if (first_play == 2)
            // gameover padrao
            break;

        // continua o jogo
        printf("Pontuacao atual do jogador %s: %d\n", p1->color, st_view_size(p1->points));

        int second_play = game_round(board, hand, p2);

        if (second_play == 1)
            withdrawal(board, p1);

        else if (second_play == 2)
            break;

        printf("Pontuacao atual do jogador %s: %d\n", p2->color, st_view_size(p2->points));
    }

    destroy_board(board);
    free_hand(hand);
    printf("\nTabuleiro excluido com sucesso, obrigado por jogar!\n");

    return 0;
}
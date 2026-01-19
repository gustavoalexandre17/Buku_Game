#include "../include/board.h"
#include "../include/game.h"
#include "../include/hand.h"
#include "../include/player.h"
#include <stdio.h>

int main()
{
    Board *board = create_board();
    Hand *hand = create_hand(view_board_size(board));

    Player *p1 = create_player("vermelho");
    Player *p2 = create_player("azul");

    init_board(board);
    show_board(board);

    while (1)
    {
        game_round(board, hand, p1);
        check_points(board, p1, p2);

        game_round(board, hand, p2);
        check_points(board, p1, p2);
    }

    destroy_board(board);
    free_hand(hand);
    printf("\nTabuleiro excluido com sucesso, obrigado por jogar!\n");

    return 0;
}
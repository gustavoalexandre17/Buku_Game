#include "../include/board.h"
#include "../include/hand.h"
#include <stdio.h>

int main(void)
{
    /* O numero te linhas tem que ser igual ao numero de colunas */
    printf("\nDigite o numero de linhas e colunas do seu tabuleiro:\n");
    int row, col;
    scanf("%d %d", &row, &col);

    Board board = createBoard(row, col);
    Hand hand = createHand();
    printf("\nTabuleiro criado com sucesso!\n");

    initBoard(&board);
    printf("\nInicializando o tabuleiro...\n");

    showBoard(&board);

    printf("Vez do jogador 1:\n");
    printf("Selecione a linha:\n");
    int playedRow;
    scanf("%d", &playedRow);

    while (playedRow < 0 || playedRow > row)
    {
        printf("Linha inválida, por favor, digite uma linha válida!\n");
        scanf("%d", &playedRow);
    }

    pick_row(&hand, &board, playedRow, row);

    printf("O tamanho da mão é de: %d\n", view_size(hand.pieces));

    printf("Vez do jogador 2:\n");
    printf("Selecione a Coluna:\n");
    int playedCol;
    scanf("%d", &playedCol);

    while (playedCol < 0 || playedCol > col)
    {
        printf("Coluna inválida, por favor, digite uma coluna válida!\n");
        scanf("%d", &playedCol);
    }

    pick_col(&hand, &board, playedCol, col);

    printf("O tamanho da mão é de: %d\n", view_size(hand.pieces));

    destroyBoard(&board);
    printf("\nTabuleiro excluido com sucesso, obrigado por jogar!\n");

    return 0;
}

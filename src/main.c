#include "board.h"
#include <stdio.h>

int main(void)
{
    /* O numero te linhas tem que ser igual ao numero de colunas */
    printf("\nDigite o numero de linhas e colunas do seu tabuleiro:\n");
    int row, col;
    scanf("%d %d", &row, &col);

    Board board = createBoard(row, col);
    printf("\nTabuleiro criado com sucesso!\n");

    initBoard(&board);
    printf("\nInicializando o tabuleiro...\n");

    showBoard(&board);

    destroyBoard(&board);
    printf("\nTabuleiro excluido com sucesso, obrigado por jogar!\n");

    return 0;
}

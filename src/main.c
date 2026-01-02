#include "../include/board.h"
#include "../include/hand.h"
#include <stdio.h>

int main()
{
    printf("\nDigite o numero de linhas e colunas do seu tabuleiro:\n");
    int row, col;
    scanf("%d %d", &row, &col);

    Board *board = createBoard(row, col);
    if (!board)
    {
        printf("Erro ao criar tabuleiro.\n");
        return 1;
    }
    printf("\nTabuleiro criado com sucesso!\n");

    Hand *hand = createHand();
    printf("\nHand criada com sucesso!\n");

    initBoard(board);
    printf("\nInicializando o tabuleiro...\n\n");

    showBoard(board);

    printf("Vez do jogador 1:\n");
    printf("Selecione a linha (1 a %d):\n", row);
    int playedRow;
    scanf("%d", &playedRow);

    while (playedRow < 1 || playedRow > row)
    {
        printf("Linha inválida, por favor, digite uma linha válida!\n");
        scanf("%d", &playedRow);
    }
    pick_row(hand, board, playedRow - 1, board->cols);
    printf("O tamanho da mao e de: %d\n", hand_size(hand));

    printf("Vez do jogador 2:\n");
    printf("Selecione a Coluna (1 a %d):\n", col);

    int playedCol;
    scanf("%d", &playedCol);

    while (playedCol < 1 || playedCol > col)
    {
        printf("Coluna inválida, por favor, digite uma coluna válida!\n");
        scanf("%d", &playedCol);
    }

    pick_col(hand, board, playedCol - 1, board->rows);
    printf("O tamanho da mao e de: %d\n", hand_size(hand));

    showBoard(board);

    destroyBoard(board);
    free_hand(hand);
    printf("\nTabuleiro excluido com sucesso, obrigado por jogar!\n");

    return 0;
}
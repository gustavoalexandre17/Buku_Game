#include "../include/board.h"
#include "../include/hand.h"
#include "../include/makeMove.h"
#include <stdio.h>

int main()
{
    // Variáveis usadas:
    int row, col, playedRow, playedCol;
    int inicializador = 1;
    Board *board;
    Hand *hand;
    playedHand *play;

    printf("\nDigite o numero de linhas e colunas do seu tabuleiro:\n");
    scanf("%d %d", &row, &col);

    board = createBoard(row, col);

    if (!board)
    {
        printf("Erro ao criar tabuleiro.\n");
        return 1;
    }

    printf("\nTabuleiro criado com sucesso!\n");

    hand = createHand();
    printf("\nHand criada com sucesso!\n");

    initBoard(board);
    printf("\nInicializando o tabuleiro...\n\n");

    showBoard(board);

    while (inicializador)
    {

        // Loop Jogador 1:
        printf("Vez do jogador 1:\n");
        printf("Selecione a linha (1 a %d):\n", row);
        scanf("%d", &playedRow);

        while (playedRow < 1 || playedRow > row)
        {
            printf("Linha inválida, por favor, digite uma linha válida!\n");
            scanf("%d", &playedRow);
        }

        pick_row(hand, board, playedRow - 1, board->cols);

        printf("\nEstado atual: \n");
        showBoard(board);

        printf("\nO tamanho da mao e de: %d\n", hand_size(hand));

        play = createPlayedHand(hand_size(hand));

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

        if (validateTotalMove(play, row))
        {
            printf("\nJogada válida\n");
        }
        else
        {
            printf("\nJogada inválida\n");
        }

        put_hand(hand, board, play);

        showBoard(board);

        for (int i = 0; i < hand_size(hand); i++)
        {
            printf("{%d,%d} ", play[i].row, play[i].col);
        }

        printf("\n");

        // Loop jogador 2:

        printf("\nVez do jogador 2:\n");
        printf("Selecione a Coluna (1 a %d):\n", col);

        scanf("%d", &playedCol);

        while (playedCol < 1 || playedCol > col)
        {
            printf("Coluna inválida, por favor, digite uma coluna válida!\n");
            scanf("%d", &playedCol);
        }

        pick_col(hand, board, playedCol - 1, board->rows);

        printf("\nEstado atual: \n");
        showBoard(board);

        printf("\nO tamanho da mao e de: %d\n", hand_size(hand));

        showBoard(board);

        play = createPlayedHand(hand_size(hand));

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

        if (validateTotalMove(play, row))
        {
            printf("\nJogada válida\n");
        }
        else
        {
            printf("\nJogada inválida\n");
        }

        put_hand(hand, board, play);

        showBoard(board);

        for (int i = 0; i < hand_size(hand); i++)
        {
            printf("{%d,%d} ", play[i].row, play[i].col);
        }

        printf("\n");
    }

    destroyBoard(board);
    free_hand(hand);
    printf("\nTabuleiro excluido com sucesso, obrigado por jogar!\n");

    return 0;
}

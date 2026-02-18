#include "../../include/domain/hand.h"
#include "../../include/domain/board.h"
#include "../../include/domain/stack.h"
#include <stdlib.h>

Hand *create_hand(int board_size) {
    Hand *newHand = (Hand *)malloc(sizeof(Hand));

    if (!newHand)
        return NULL;

    newHand->pieces = create_stack();

    if (board_size % 2 == 0)
        insert_stack(newHand->pieces, 'O');
    return newHand;
}

int pick_row(Hand *hand, Board *board, int row, int size) {
    if (!hand || !board)
        return -1;

    for (int i = 0; i < size; i++) {
        while (st_view_size(board->cells[row][i]) > 0) {
            insert_stack(hand->pieces, 'O');
            pop_stack(board->cells[row][i]);
        }
    }
    return 0;
}

int pick_col(Hand *hand, Board *board, int col, int size) {
    if (!hand || !board)
        return -1;

    for (int i = 0; i < size; i++) {
        while (st_view_size(board->cells[i][col]) > 0) {
            insert_stack(hand->pieces, 'O');
            pop_stack(board->cells[i][col]);
        }
    }
    return 0;
}

int put_hand(Hand *hand, Board *board, PlayedHand *ph) {
    if (!hand || !board || !ph)
        return 0;

    int tamanho = hand_size(hand);

    for (int i = 0; i < tamanho; i++) {
        insert_stack(board->cells[ph[i].row][ph[i].col], st_view_top(hand->pieces));
        pop_stack(hand->pieces);
    }
    return 1;
}

int hand_size(Hand *hand) { return st_view_size(hand->pieces); }

int free_hand(Hand *hand) {
    if (!hand)
        return -1;

    free_stack(hand->pieces);
    free(hand);
    return 0;
}

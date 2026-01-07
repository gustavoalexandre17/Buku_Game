#include "../include/move.h"
#include <stdio.h>
#include <stdlib.h>

PlayedHand *create_played_hand(int size)
{
    PlayedHand *newPH = (PlayedHand *)malloc(size * sizeof(PlayedHand));

    if (!newPH)
        return NULL;

    newPH->size = size;

    return newPH;
}

/*Passievel de refatoracao*/
int validate_full_move(PlayedHand *ph, int boardSize)
{
    if (!ph)
        return 0;

    for (int i = 0; i < ph->size; i++)
    {
        if (!validate_parcial_move(ph[i].row, ph[i].col, boardSize))
            return 0;

        else if (i != 0)
        {
            int totalNeighbor = 4;
            int Neighbors[4][2] = {{ph[i - 1].row, ph[i - 1].col + 1},
                                   {ph[i - 1].row, ph[i - 1].col - 1},
                                   {ph[i - 1].row + 1, ph[i - 1].col},
                                   {ph[i - 1].row - 1, ph[i - 1].col}};

            // Verificar se é vizinho

            int test = 0;
            test += is_neighbor(ph[i], Neighbors[0][0], Neighbors[0][1]);
            test += is_neighbor(ph[i], Neighbors[1][0], Neighbors[1][1]);
            test += is_neighbor(ph[i], Neighbors[2][0], Neighbors[2][1]);
            test += is_neighbor(ph[i], Neighbors[3][0], Neighbors[3][1]);

            if (test == 1)
            {
                Neighbors[0][0] = ph[i].row;
                Neighbors[0][1] = ph[i].col + 1;

                Neighbors[1][0] = ph[i].row;
                Neighbors[1][1] = ph[i].col - 1;

                Neighbors[2][0] = ph[i].row + 1;
                Neighbors[2][1] = ph[i].col;

                Neighbors[3][0] = ph[i].row - 1;
                Neighbors[3][1] = ph[i].col;

                for (int j = 0; j < 4; j++)
                    if (!validate_parcial_move(Neighbors[j][0], Neighbors[j][1], boardSize) ||
                        already_played(Neighbors[j][0], Neighbors[j][1], i, ph))
                        totalNeighbor--;
            }
            else
                return 0;

            if (totalNeighbor == 0)
                return 0;
        }
    }
    return 1;
}

int validate_parcial_move(int row, int col, int boardSize)
{
    if (col < 0 || row < 0 || col > boardSize || row > boardSize)
        return 0;

    return 1;
}

int is_neighbor(PlayedHand ph, int row, int col)
{
    if (ph.row == row && ph.col == col)
        return 1;

    return 0;
}

int already_played(int row, int col, int index, PlayedHand *ph)
{
    for (int i = 0; i < index; i++)
    {
        if (row == ph[i].row && col == ph[i].col)
            return 1;
    }
    return 0;
}

void free_played_hand(PlayedHand *ph) { free(ph); }
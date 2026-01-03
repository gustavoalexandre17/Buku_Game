#include "../include/makeMove.h"
#include <stdio.h>
#include <stdlib.h>

playedHand *createPlayedHand(int size)
{
    playedHand *newPlayedHand = (playedHand *)malloc(size * sizeof(playedHand));

    if (!newPlayedHand)
        return NULL;

    newPlayedHand->size = size;

    return newPlayedHand;
}

int validateParcialMove(int row, int col, int boardSize)
{
    if (col < 0 || row < 0 || col > boardSize || row > boardSize)
    {
        return 0;
    }
    return 1;
}

int isNeighbor(playedHand ph, int row, int col)
{
    if (ph.row == row && ph.col == col)
    {
        return 1;
    }
    return 0;
}

int isAlreadyPlayed(int row, int col, int index, playedHand *ph)
{
    for (int i = 0; i < index; i++)
    {
        if (row == ph[i].row && col == ph[i].col)
        {
            return 1;
        }
    }
    return 0;
}

int validateTotalMove(playedHand *ph, int boardSize)
{
    if (!ph)
        return 0;

    for (int i = 0; i < ph->size; i++)
    {
        if (!validateParcialMove(ph[i].row, ph[i].col, boardSize))
        {
            return 0;
        }
        else if (i != 0)
        {
            int totalNeighbor = 4;
            int Neighbors[4][2] = {{ph[i - 1].row, ph[i - 1].col + 1},
                                   {ph[i - 1].row, ph[i - 1].col - 1},
                                   {ph[i - 1].row + 1, ph[i - 1].col},
                                   {ph[i - 1].row - 1, ph[i - 1].col}};

            // Verificar se é vizinho;
            int teste = 0;
            teste += isNeighbor(ph[i], Neighbors[0][0], Neighbors[0][1]);
            teste += isNeighbor(ph[i], Neighbors[1][0], Neighbors[1][1]);
            teste += isNeighbor(ph[i], Neighbors[2][0], Neighbors[2][1]);
            teste += isNeighbor(ph[i], Neighbors[3][0], Neighbors[3][1]);

            if (teste == 1)
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
                {
                    if (!validateParcialMove(Neighbors[j][0], Neighbors[j][1], boardSize) ||
                        isAlreadyPlayed(Neighbors[j][0], Neighbors[j][1], i, ph))
                    {
                        totalNeighbor--;
                    }
                }
            }
            else
            {
                return 0;
            }

            if (totalNeighbor == 0)
            {
                return 0;
            }
        }
    }

    return 1;
}

void freePlayedHand(playedHand *ph) { free(ph); }

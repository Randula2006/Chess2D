#ifndef BOARD_H
#define BOARD_H

#include "piece.h"

#define BOARD_SIZE 9 /* rows and cols in chess board */

typedef struct{
    Piece squares[BOARD_SIZE][BOARD_SIZE];
}Board;


void initBoard(Board * board);
void initPieces(Board * board);

#endif
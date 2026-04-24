#ifndef MOVES_H
#define MOVES_H

#include "board.h"

#define MAX_MOVES 28 /* max number = 27// +1 for safety */

typedef struct{
    int currentRow;
    int currentCol;
    int targetRow;
    int targetCol;
}Move;

typedef struct{
    Move moves[MAX_MOVES];
    int count;
}MoveList;


void getMoves(Board * board, int row, int col, MoveList * list);


#endif
#ifndef MOVES_H
#define MOVES_H

#include "board.h"

#define MAX_MOVES 64

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
void KingMovement(Board *board , MoveList * list, int row, int col);
void RookMovement(Board *board , MoveList * list, int row, int col);
void BishopMovement(Board *board , MoveList * list, int row, int col);
void KnightMovement(Board *board , MoveList * list, int row, int col);
void PawnMovement(Board *board , MoveList * list, int row, int col);
void movePiece(Board * board, MoveList * list, int row, int col, int i, int j); 
int isInCheck(Board *board, PieceColor color);
void filterLegalMoves(Board * board, MoveList * list, PieceColor color);
int hasAnyLegalMoves(Board * board, PieceColor color);

#endif
#include <stdio.h>
#include "moves.h"
#include "../include/board.h"


void getMoves(Board * board, int row, int col, MoveList * list){
    if(board->squares[row][col].pieceType == KING){
        KingMovement(board, list, row, col);
    }

}


void KingMovement(Board * board, MoveList * list, int row, int col){
    int i, j;
    list->count = 0;

    /* get all valid moves */
    for(i = -1; i <= 1; i++){
        for(j = -1; j <= 1; j++){
            /* checks for invalid conditions */
            if(i == 0 && j == 0) continue;
            if(row + i < 1 || row + i > 8 || col + j < 1 || col + j > 8) continue;
            if(board->squares[row + i][col + j].color == board->squares[row][col].color) continue;

            list->moves[list->count].currentRow = row;
            list->moves[list->count].currentCol = col;
            list->moves[list->count].targetRow = row + i;
            list->moves[list->count].targetCol = col + j;
            list->count++;
        }
    }
}
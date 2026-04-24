#include <stdio.h>
#include "moves.h"
#include "../include/board.h"


void getMoves(Board * board, int row, int col, MoveList * list){
    if(board->squares[row][col].pieceType == KING){
        KingMovement(board, list, row, col);
    }else if (board->squares[row][col].pieceType == ROOK){
        RookMovement(board, lsit, row, col);
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

void RookMovement(Board *board , MoveList * list, int row, int col){
    int i = 1;

    /* get valid moves for Up direction */
    while(i < BOARD_SIZE){
        if(row - i < 1) break;
        if(board->squares[row -i][col].pieceType != EMPTY){
            if(board->squares[row -i][col].color != board->squares[row][col].color){
                movePiece(board, list, row, col, -i, 0);
            }
            break;
        }
        
        movePiece(board, list, row, col, -i, 0);
        i++;
    }

    /* get valid moves for down direction */
    i = 1;
    while(i < BOARD_SIZE){
        if(row + i > 8) break;
        if(board->squares[row +i][col].pieceType != EMPTY){
            if(board->squares[row + i][col].color != board->squares[row][col].color){
                movePiece(board, list, row, col, +i, 0);
            }
            break;
        }
        
        movePiece(board, list, row, col, +i, 0);
        i++;
    }

    /* get valid moves for right direction */
    i = 1;
    while(i < BOARD_SIZE){
        if(col+ i > 8) break;
        if(board->squares[row][col + i].pieceType != EMPTY){
            if(board->squares[row][col + i].color != board->squares[row][col].color){
                movePiece(board, list, row, col, 0, +i);
            }
            break;
        }
        
        movePiece(board, list, row, col, 0, +i);
        i++;   
    }   

    
    /* get valid moves for left direction */
    i = 1;
    while(i < BOARD_SIZE){
        if(col -i < 1) break;
        if(board->squares[row][col - i].pieceType != EMPTY){
            if(board->squares[row][col - i].color != board->squares[row][col].color){
                movePiece(board, list, row, col, 0, -i);
            }
            break;
        }
        
        movePiece(board, list, row, col, 0, -i);
        i++;
    }   


}

void BishopMovement(Board *board , MoveList * list, int row, int col){
    int i = 1;

    /* get valid moves for Up-right direction */
    while(i < BOARD_SIZE){
        if((row - i) < 1 || (col + i) > 8) break;
        if(board->squares[row - i][col + i].pieceType != EMPTY){
            if(board->squares[row - i][col + i].color != board->squares[row][col].color){
                movePiece(board, list, row, col, -i, +i);
            }
            break;
        }
        
        movePiece(board, list, row, col, -i, +i);
        i++;
    }

    /* get valid moves for down-right direction */
    i = 1;
    while(i < BOARD_SIZE){
        if((row + i) > 8 || (col + i) > 8) break;
        if(board->squares[row + i][col + i].pieceType != EMPTY){
            if(board->squares[row + i][col + i].color != board->squares[row][col].color){
                movePiece(board, list, row, col, +i, +i);
            }
            break;
        }
        
        movePiece(board, list, row, col, +i, +i);
        i++;
    }

    /* get valid moves for down-left direction */
    i = 1;
    while(i < BOARD_SIZE){
        if((row + i) > 8 || (col - i) < 1) break;
        if(board->squares[row + i][col - i].pieceType != EMPTY){
            if(board->squares[row + i][col - i].color != board->squares[row][col].color){
                movePiece(board, list, row, col, +i, -i);
            }
            break;
        }
        
        movePiece(board, list, row, col, +i, -i);
        i++;   
    }   

    
    /* get valid moves for up-left direction */
    i = 1;
    while(i < BOARD_SIZE){
        if((row - i) < 1 || (col -i) < 1) break;
        if(board->squares[row - i][col - i].pieceType != EMPTY){
            if(board->squares[row - i][col - i].color != board->squares[row][col].color){
                movePiece(board, list, row, col, -i, -i);
            }
            break;
        }

        movePiece(board, list, row, col, -i, -i);
        i++;
    } 


}


void movePiece(Board * board, MoveList * list, int row, int col, int i, int j){
        list->moves[list->count].currentRow = row;
        list->moves[list->count].currentCol = col;
        list->moves[list->count].targetRow = row + i;
        list->moves[list->count].targetCol = col + j;
        list->count++;
}
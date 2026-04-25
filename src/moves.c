#include <stdio.h>
#include "moves.h"
#include "../include/board.h"


void getMoves(Board * board, int row, int col, MoveList * list){
    list->count = 0;
    if(board->squares[row][col].pieceType == KING){
        KingMovement(board, list, row, col);
    }else if (board->squares[row][col].pieceType == ROOK){
        RookMovement(board, list, row, col);
    }else if(board->squares[row][col].pieceType == BISHOP){
        BishopMovement(board, list, row, col);
    }else if(board->squares[row][col].pieceType == QUEEN){
        RookMovement(board, lsit, row, col);
        BishopMovement(board, list, row, col);
    }else if(board->squares[row][col].pieceType == KNIGHT){
        KnightMovement(board, list, row, col);
    }else if(board->squares[row][col].pieceType == PAWN){
        PawnMovement(board, list, row, col);
    }

}


void KingMovement(Board * board, MoveList * list, int row, int col){
    int i, j;

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

void KnightMovement(Board *board , MoveList * list, int row, int col){
    int i;
    int offsets[8][2] = {
        {-2, -1},
        {-2, +1},
        {-1, -2},
        {-1, +2},
        {+1, -2},
        {+1, +2},
        {+2, -1},
        {+2, +1}
    };

    
    for(i = 0; i < 8; i++){
            if ( row + offsets[i][0] < 1 || row + offsets[i][0] > 8 || col + offsets[i][1] < 1 || col + offsets[i][1] > 8) continue;
            if (board->squares[row + offsets[i][0] ][col + offsets[i][1]].pieceType != EMPTY){
                if (board->squares[row + offsets[i][0]][col + offsets[i][1]].color != board->squares[row][col].color){
                    movePiece(board, list, row, col, offsets[i][0], offsets[i][1]);
                }
                continue;
            }

            movePiece(board, list, row, col, offsets[i][0], offsets[i][1]);
            
    }

}

void PawnMovement(Board *board , MoveList * list, int row, int col){
    /* Black Pawn movement - rows increases */ 
    if(board->squares[row][col].color == BLACK){

        if(row + 1 > 8) return;
        if(board->squares[row + 1][col].pieceType != EMPTY) return;
        movePiece(board, list, row, col, +1, 0);

        /* First Move */
        if(row == 2 && board->squares[row+2][col].pieceType == EMPTY){
            movePiece(board, list, row, col, +2, 0);
        }

        /* capture piece to right */
        if((col+1) < BOARD_SIZE && 
           board->squares[row + 1][col + 1].pieceType != EMPTY && 
           board->squares[row + 1][col + 1].color != BLACK ){
            movePiece(board, list, row, col, +1, +1);
           }
        
        /* capture piece to left */
        if((col-1) >= 1 &&
           board->squares[row + 1][col - 1].pieceType != EMPTY && 
           board->squares[row + 1][col - 1].color != BLACK ){
            movePiece(board, list, row, col, +1, -1);
           }
        

    }

    /* White Pawn Movement - Rows decreases */
    if(board->squares[row][col].color == WHITE){

        if(row - 1 < 1) return;
        if(board->squares[row - 1][col].pieceType != EMPTY) return;
        movePiece(board, list, row, col, -1, 0);

        /* First Move */
        if(row == 7 && board->squares[row-2][col].pieceType == EMPTY){
            movePiece(board, list, row, col, -2, 0);
        }

        /* capture piece to right */
        if((col+1) < BOARD_SIZE &&
           board->squares[row - 1][col + 1].pieceType != EMPTY && 
           board->squares[row - 1][col + 1].color != WHITE ){
            movePiece(board, list, row, col, -1, +1);
           }
        
        /* capture piece to left */
        if((col-1) >= 1 &&
           board->squares[row - 1][col - 1].pieceType != EMPTY && 
           board->squares[row - 1][col - 1].color != WHITE ){
            movePiece(board, list, row, col, -1, -1);
           }
    }
}

void movePiece(Board * board, MoveList * list, int row, int col, int i, int j){
        list->moves[list->count].currentRow = row;
        list->moves[list->count].currentCol = col;
        list->moves[list->count].targetRow = row + i;
        list->moves[list->count].targetCol = col + j;
        list->count++;
}
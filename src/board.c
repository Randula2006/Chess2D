
#include <stdio.h>
#include <stdlib.h> 
#include "../include/board.h"

void initBoard(Board * board){
    int row, col;

    for(row = 1; row <= BOARD_SIZE; row++){
        for(col = 1; col <= BOARD_SIZE; col++){

            board-> squares[row][col].pieceType = EMPTY;
            
            /* Set a default color to the board */
            if((col % 2) == 1){
                board-> squares[row][col].color = BLACK;
            }else{
                board-> squares[row][col].color = WHITE;
            }
        }
    }

    /* Hard code pieces as they do not change initially */
    initPieces(board);

}

void initPieces(Board * board){
    int i;
    /* hard coding the chess pieces as they do not change */
    
    /* Pawns */
    for(i = 1; i <= BOARD_SIZE; i++){
        board-> squares[2][i].pieceType = PAWN; 
        board-> squares[7][i].pieceType = PAWN; 
    }

    /* Bishop */
    board-> squares[1][3].pieceType = BISHOP;
    board-> squares[1][6].pieceType = BISHOP;
    board-> squares[8][3].pieceType = BISHOP;
    board-> squares[8][6].pieceType = BISHOP;

    /* Knight */
    board-> squares[1][2].pieceType = KNIGHT;
    board-> squares[1][7].pieceType = KNIGHT;
    board-> squares[8][2].pieceType = KNIGHT;
    board-> squares[8][7].pieceType = KNIGHT;

    /* Rook */
    board-> squares[1][1].pieceType = ROOK;
    board-> squares[1][8].pieceType = ROOK;
    board-> squares[8][1].pieceType = ROOK;
    board-> squares[8][8].pieceType = ROOK;

    /* Queen */
    board-> squares[1][4].pieceType = QUEEN;
    board-> squares[8][4].pieceType = QUEEN;

    /* King */
    board-> squares[1][5].pieceType = KING;
    board-> squares[8][5].pieceType = KING;

}
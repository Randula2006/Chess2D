
#include <stdio.h>
#include <stdlib.h> 
#include "../include/board.h"

void initBoard(Board * board){
    int row, col;

    for(row = 1; row < BOARD_SIZE; row++){ /* starts from 1 until 8 . 0th index kept free. */
        for(col = 1; col < BOARD_SIZE; col++){

            board-> squares[row][col].pieceType = EMPTY;
            board-> squares[row][col].color = NONE;
        }
    }

    /* Hard code pieces as they do not change initially */
    initPieces(board);

}

void initPieces(Board * board){
    int i;
    /* hard coding the chess pieces as they do not change */
    
    /* Pawns */
    for(i = 1; i < BOARD_SIZE; i++){
        board-> squares[2][i].pieceType = PAWN; 
        board-> squares[2][i].color = BLACK;

        board-> squares[7][i].pieceType = PAWN;
        board-> squares[7][i].color = WHITE;
    }

    /* Bishop */
    board-> squares[1][3].pieceType = BISHOP;
    board-> squares[1][6].pieceType = BISHOP;
    board-> squares[1][3].color = BLACK;
    board-> squares[1][6].color = BLACK;

    board-> squares[8][3].pieceType = BISHOP;
    board-> squares[8][6].pieceType = BISHOP;
    board-> squares[8][3].color = WHITE;
    board-> squares[8][6].color = WHITE;

    /* Knight */
    board-> squares[1][2].pieceType = KNIGHT;
    board-> squares[1][7].pieceType = KNIGHT;
    board-> squares[1][2].color = BLACK;
    board-> squares[1][7].color = BLACK;

    board-> squares[8][2].pieceType = KNIGHT;
    board-> squares[8][7].pieceType = KNIGHT;
    board-> squares[8][2].color = WHITE;
    board-> squares[8][7].color = WHITE;

    /* Rook */
    board-> squares[1][1].pieceType = ROOK;
    board-> squares[1][8].pieceType = ROOK;
    board-> squares[1][1].color = BLACK;
    board-> squares[1][8].color = BLACK;

    board-> squares[8][1].pieceType = ROOK;
    board-> squares[8][8].pieceType = ROOK;
    board-> squares[8][1].color = WHITE;
    board-> squares[8][8].color = WHITE;

    /* Queen */
    board-> squares[1][4].pieceType = QUEEN;
    board-> squares[1][4].color = BLACK;

    board-> squares[8][4].pieceType = QUEEN;
    board-> squares[8][4].color = WHITE;

    /* King */
    board-> squares[1][5].pieceType = KING;
    board-> squares[1][5].color = BLACK;

    board-> squares[8][5].pieceType = KING;
    board-> squares[8][5].color = WHITE;
}
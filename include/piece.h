#ifndef PIECE_H
#define PIECE_H

typedef enum{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    EMPTY
}PieceType;

typedef enum{
    BLACK,
    WHITE,
    NONE
}PieceColor;


typedef struct{
   PieceType pieceType;
   PieceColor color;
}Piece;


#endif
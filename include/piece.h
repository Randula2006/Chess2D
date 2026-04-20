#ifndef PIECE_H
#define PIECE_H

typedef enum{
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King,
    empty
}PieceType;

typedef enum{
    Black,
    White,
    empty
}PieceColor;


typedef struct{
   PieceType pieceType;
   PieceColor color;
}Piece;


#endif
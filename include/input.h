#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "../include/moves.h"

typedef struct{
    int selectedRow;
    int selectedCol;
    MoveList availableMoves;
    PieceColor currentTurn;
    int gameOver; /* 0 for active, 1 for game over */
}GameState;


void HandleInput(SDL_Event * event, GameState * state, Board * board);
int isValidMove(MoveList * list, int row, int col);
void applyMove(Board* board, Move* move);

#endif
#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "../include/moves.h"

typedef struct{
    int selectedRow;
    int selectedCol;
    MoveList availableMoves;
}GameState;


void HandleInput(SDL_Event * event, GameState * state, Board * board);
int isValidMove(MoveList * list, int row, int col);
void applyMove(Board* board, Move* move);

#endif
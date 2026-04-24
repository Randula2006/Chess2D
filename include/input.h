#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

typedef struct{
    int selectedRow;
    int selectedCol;
}GameState;


void HandleInput(SDL_Event * event, GameState * state);

#endif
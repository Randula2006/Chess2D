#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "board.h"

#define BLOCK_SIZE 100

void render_board(SDL_Renderer* renderer, Board* board);


#endif
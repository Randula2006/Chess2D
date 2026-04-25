#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "board.h"
#include "input.h"

#define BLOCK_SIZE 100

typedef struct{
    SDL_Texture * pieces[2][6]; /* as 2 x 6 means 12 pieces as in chess*/
} Textures;


void render_board(SDL_Renderer* renderer, Board* board);
void load_pieces(SDL_Renderer* renderer, Textures * textures);
void render_pieces(Board * board, Textures * textures, SDL_Renderer* renderer);
void render_selection(SDL_Renderer * renderer, GameState * state);
void render_moves(SDL_Renderer * renderer, MoveList * list);

#endif
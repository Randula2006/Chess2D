
#include "../include/render.h"



void render_board(SDL_Renderer* renderer, Board* board){
    SDL_Rect fillRect;
    int row, col;
    int rowStart, colStart;

    for(row = 1; row < BOARD_SIZE; row++){
        for(col = 1; col < BOARD_SIZE; col++){

            rowStart = (row-1) * 100;
            colStart = (col-1) * 100;
            
            fillRect = (SDL_Rect){ rowStart, colStart, BLOCK_SIZE, BLOCK_SIZE };

            /* starts from 1 and not from 0 */
            /* Black */
            if(((row + col) % 2) == 1){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &fillRect);

            }else{ /* White */
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &fillRect);
            }

        }
    }
}
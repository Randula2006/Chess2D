#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/board.h"
#include "../include/render.h"
#include "../include/input.h"


int main(int argc, char* argv[]){
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    Textures textures;
    SDL_Event event; 
    Board board;
    GameState state;
    int running = 1;

    int result = SDL_Init(SDL_INIT_VIDEO);
    
    /* If SDL init fils*/
    if(result != 0){
        printf("%s\n", SDL_GetError());
        return 1;
    }

    result = IMG_Init(IMG_INIT_PNG);
    if (!(result & IMG_INIT_PNG))
    { // if PNG was NOT successfully initialized
        printf("%s\n", IMG_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "Chess 2D",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        800,
        SDL_WINDOW_SHOWN
    );
    /* If create window fails*/
    if(window == NULL){
        printf("%s\n", SDL_GetError());
        return 1;
    }


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
        printf("%s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    /* Create the chess board with pieces in the memory */
    initBoard(&board);

    /* loading pieces into the memory */
    load_pieces(renderer, &textures);

    state.selectedRow = -1;
    state.selectedCol = -1;

    while(running == 1){
        /* poll events */
        while (SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = 0;
            }

            /* Handle user input*/
            HandleInput(&event, &state);
        }

        SDL_SetRenderDrawColor(renderer, 20, 80, 20, 255);
        SDL_RenderClear(renderer);

        /* render the checkerboard pattern and pieces on the window*/
        render_board(renderer, &board);
        render_pieces(&board, &textures, renderer);

        /* render user selected square from handleInput */
        render_selection(renderer, &state);

        SDL_RenderPresent(renderer);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
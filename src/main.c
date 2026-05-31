#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/board.h"
#include "../include/render.h"
#include "../include/input.h"
#include "../include/moves.h"


int main(int argc, char* argv[]){
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    Textures textures;
    SDL_Event event; 
    Board board;
    GameState state;
    int running = 1;

    int result = SDL_Init(SDL_INIT_VIDEO);
    if(result != 0){
        printf("%s\n", SDL_GetError());
        return 1;
    }

    result = IMG_Init(IMG_INIT_PNG);
    if (!(result & IMG_INIT_PNG)){
        printf("%s\n", IMG_GetError());
        return 1;
    }

    result = TTF_Init();
    if (TTF_Init() != 0){
        printf("%s\n", TTF_GetError());
        return 1;
    }

    TTF_Font * font = TTF_OpenFont("assets/Bungee-Regular.ttf", 48);
    if (font == NULL){
        printf("%s\n", TTF_GetError());
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

    SDL_SetWindowResizable(window, SDL_FALSE);

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

    initBoard(&board);
    load_pieces(renderer, &textures);

    state.selectedRow = -1;
    state.selectedCol = -1;
    state.currentTurn = WHITE;
    state.availableMoves.count = 0;
    state.gameOver = 0;
    state.winner = NONE;
    
    while(running == 1){
        while (SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = 0;
            }

            if(event.type == SDL_WINDOWEVENT){
                if(event.window.event == SDL_WINDOWEVENT_RESIZED ||
                   event.window.event == SDL_WINDOWEVENT_MAXIMIZED){
                    SDL_SetWindowSize(window, 800, 800);
                    SDL_RestoreWindow(window);
                }
            }

            HandleInput(&event, &state, &board);
        }

        SDL_SetRenderDrawColor(renderer, 20, 80, 20, 255);
        SDL_RenderClear(renderer);

        render_board(renderer, &board);
        render_pieces(&board, &textures, renderer);
        render_selection(renderer, &state);
        render_moves(renderer, &state.availableMoves);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
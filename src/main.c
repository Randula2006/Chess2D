#include <stdio.h>
#include <SDL2/SDL.h>


int main(int argc, char* argv[]){
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Event event; 
    int running = 1;

    int result = SDL_Init(SDL_INIT_VIDEO);
    
    /* If SDL init fils*/
    if(result != 0){
        printf("%s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "CHess 2D",
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


    while(running == 1){
        /* poll events */
        while (SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 20, 80, 20, 255);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
#include "../include/input.h"
#include <SDL2/SDL.h>
#include <stdio.h>


void HandleInput(SDL_Event * event, GameState * state){
    int x,y;

    if(event->type == SDL_MOUSEBUTTONDOWN){
        if(event->button.button == SDL_BUTTON_LEFT){
            printf("Left mouse clicked");
            x = event->button.x;
            y = event->button.y;

            state->selectedRow = (y / 100) + 1;
            state->selectedCol = (x / 100) + 1;
        }
    }


}
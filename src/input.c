#include "../include/input.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "../include/moves.h"
#include "../include/board.h"


void HandleInput(SDL_Event * event, GameState * state, Board * board){
    int isValidSelection;

    if(event->type == SDL_MOUSEBUTTONDOWN){
        if(event->button.button == SDL_BUTTON_LEFT){
            /* printf("Left mouse clicked\n"); */

            if(state->selectedRow == -1){
                state->selectedRow = (event->button.y / 100) + 1;
                state->selectedCol = (event->button.x / 100) + 1;

                getMoves(board, state->selectedRow, state->selectedCol, &state->availableMoves);
            
            }else{

                isValidSelection = isValidMove(&state->availableMoves, state->selectedRow, state->selectedCol);
                
                if(isValidSelection == 1){
                    /* TODO: implement apply move function */
                    state->selectedRow = -1; /* Clears the selection */
                
                }else{
                    /* consider as a new selection */
                    state->selectedRow = (event->button.y / 100) + 1;
                    state->selectedCol = (event->button.x / 100) + 1;

                    getMoves(board, state->selectedRow, state->selectedCol, &state->availableMoves);
                }
            
            
            }


        }
    }


}


int isValidMove(MoveList * list, int row, int col){
    int i;
    for(i = 0; i < list->count; i++){
        if(row == list->moves[i].targetRow && col == list->moves[i].targetCol) return 1;
    }   
    return 0;
}


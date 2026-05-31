#include "../include/input.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "../include/moves.h"
#include "../include/board.h"


void HandleInput(SDL_Event * event, GameState * state, Board * board){
    int isValidSelection;
    int newRow, newCol;

    if(state->gameOver == 1) return;

    if(event->type == SDL_MOUSEBUTTONDOWN){
        if(event->button.button == SDL_BUTTON_LEFT){
            /* printf("Left mouse clicked\n"); */

            if(state->selectedRow == -1){
                state->selectedRow = (event->button.y / 100) + 1;
                state->selectedCol = (event->button.x / 100) + 1;

                if (board->squares[state->selectedRow][state->selectedCol].color != state->currentTurn){
                    state->selectedRow = -1; /* reject selection */
                    return;
                }

                getMoves(board, state->selectedRow, state->selectedCol, &state->availableMoves);

                if (state->availableMoves.count == 0){
                    state->selectedRow = -1;
                    return;
                }

            }else{

                newRow = (event->button.y / 100) + 1;
                newCol = (event->button.x / 100) + 1;
                isValidSelection = isValidMove(&state->availableMoves, newRow, newCol);
                
                if(isValidSelection == 1){                    
                    Move move;
                    move.currentRow = state->selectedRow;
                    move.currentCol = state->selectedCol;
                    move.targetRow = newRow;
                    move.targetCol = newCol;

                    applyMove(board, &move);

                    //Testing King check cases
                    /*
                    if (isInCheck(board, WHITE)){
                        printf("White king is in check!\n");
                        fflush(stdout);
                    }
                    if (isInCheck(board, BLACK)){
                        printf("Black king is in check!\n");
                        fflush(stdout);
                    }
                    */
                    state->selectedRow = -1;
                    state->availableMoves.count = 0;

                    PieceColor nextTurn;
                    if (state->currentTurn == WHITE){
                        nextTurn = BLACK;
                    }
                    else{
                        nextTurn = WHITE;
                    }
                    state->currentTurn = nextTurn;

                    if (!hasAnyLegalMoves(board, nextTurn)){
                        if (isInCheck(board, nextTurn)){
                            state->gameOver = 1;
                            if (nextTurn == WHITE){
                                printf("Checkmate! Black wins!\n");
                                state->winner = BLACK;
                            }
                            else{
                                printf("Checkmate! White wins!\n");
                                state->winner = WHITE;
                            }
                            fflush(stdout);
                        }
                        else{
                            state->gameOver = 1;
                            state->winner = NONE;
                            printf("Stalemate! It's a draw!\n");
                            fflush(stdout);
                        }
                    }
                    else if (isInCheck(board, nextTurn)){
                        if (nextTurn == WHITE)
                        {
                            printf("White is in check!\n");
                        }
                        else{
                            printf("Black is in check!\n");
                        }
                        fflush(stdout);
                    }
                }else{
                    /* consider as a new selection */
                    newRow = (event->button.y / 100) + 1;
                    newCol = (event->button.x / 100) + 1;

                    if (board->squares[newRow][newCol].color != state->currentTurn){
                        state->selectedRow = -1; /* deselect */
                        return;
                    }
                    state->selectedRow = newRow;
                    state->selectedCol = newCol;

                    getMoves(board, state->selectedRow, state->selectedCol, &state->availableMoves);

                    if (state->availableMoves.count == 0){
                        state->selectedRow = -1;
                        return;
                    }
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


void applyMove(Board* board, Move* move){
      /*  printf("Moving from %d,%d to %d,%d\n", 
           move->currentRow, move->currentCol,
           move->targetRow, move->targetCol); */
    board->squares[move->targetRow][move->targetCol] = board->squares[move->currentRow][move->currentCol];

    /*Empty the original Squares */
    board->squares[move->currentRow][move->currentCol].pieceType = EMPTY;
    board->squares[move->currentRow][move->currentCol].color = NONE;
}

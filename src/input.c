#include "../include/input.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/moves.h"
#include "../include/board.h"


void HandleInput(SDL_Event * event, GameState * state, Board * board){
    int isValidSelection;
    int newRow, newCol;

    if(state->gameOver == 1) return;

    /* Handle promotion selection */
    if(state->pendingPromotion == 1){
        if(event->type == SDL_MOUSEBUTTONDOWN){
            if(event->button.button == SDL_BUTTON_LEFT){
                int clickX = event->button.x;
                int clickY = event->button.y;

                if(clickX >= 200 && clickX <= 600 && clickY >= 350 && clickY <= 450){
                    int index = (clickX - 200) / 100;
                    int choices[4] = {QUEEN, ROOK, BISHOP, KNIGHT};

                    board->squares[state->promotionRow][state->promotionCol].pieceType = choices[index];
                    state->pendingPromotion = 0;

                    PieceColor nextTurn;
                    if(state->currentTurn == WHITE){
                        nextTurn = BLACK;
                    }else{
                        nextTurn = WHITE;
                    }
                    state->currentTurn = nextTurn;

                    if(!hasAnyLegalMoves(board, nextTurn)){
                        if(isInCheck(board, nextTurn)){
                            state->gameOver = 1;
                            if(nextTurn == WHITE){
                                printf("Checkmate! Black wins!\n");
                                state->winner = BLACK;
                            }else{
                                printf("Checkmate! White wins!\n");
                                state->winner = WHITE;
                            }
                            fflush(stdout);
                        }else{
                            state->gameOver = 1;
                            state->winner = NONE;
                            printf("Stalemate! It's a draw!\n");
                            fflush(stdout);
                        }
                    }
                }
            }
        }
        return;
    }

    if(event->type == SDL_MOUSEBUTTONDOWN){
        if(event->button.button == SDL_BUTTON_LEFT){

            if(state->selectedRow == -1){
                state->selectedRow = (event->button.y / 100) + 1;
                state->selectedCol = (event->button.x / 100) + 1;

                if(board->squares[state->selectedRow][state->selectedCol].color != state->currentTurn){
                    state->selectedRow = -1;
                    return;
                }

                getMoves(board, state->selectedRow, state->selectedCol, &state->availableMoves, state->enPassantRow, state->enPassantCol);

                if(state->availableMoves.count == 0){
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

                    /* If this was an en passant capture, remove the captured pawn */
                    if(board->squares[move.targetRow][move.targetCol].pieceType == PAWN &&
                       move.targetCol != move.currentCol &&
                       move.targetRow == state->enPassantRow &&
                       move.targetCol == state->enPassantCol){
                        board->squares[move.currentRow][move.targetCol].pieceType = EMPTY;
                        board->squares[move.currentRow][move.targetCol].color = NONE;
                    }

                    /* Set or clear en passant target for next turn */
                    if(board->squares[move.targetRow][move.targetCol].pieceType == PAWN &&
                       abs(move.targetRow - move.currentRow) == 2){
                        state->enPassantRow = (move.currentRow + move.targetRow) / 2;
                        state->enPassantCol = move.currentCol;
                    }else{
                        state->enPassantRow = -1;
                        state->enPassantCol = -1;
                    }

                    state->selectedRow = -1;
                    state->availableMoves.count = 0;

                    /* Check if a pawn just reached the last row */
                    if(board->squares[move.targetRow][move.targetCol].pieceType == PAWN){
                        if((board->squares[move.targetRow][move.targetCol].color == WHITE && move.targetRow == 1) ||
                           (board->squares[move.targetRow][move.targetCol].color == BLACK && move.targetRow == 8)){
                            state->pendingPromotion = 1;
                            state->promotionRow = move.targetRow;
                            state->promotionCol = move.targetCol;
                            return;
                        }
                    }

                    /* Switch turns */
                    PieceColor nextTurn;
                    if(state->currentTurn == WHITE){
                        nextTurn = BLACK;
                    }else{
                        nextTurn = WHITE;
                    }
                    state->currentTurn = nextTurn;

                    if(!hasAnyLegalMoves(board, nextTurn)){
                        if(isInCheck(board, nextTurn)){
                            state->gameOver = 1;
                            if(nextTurn == WHITE){
                                printf("Checkmate! Black wins!\n");
                                state->winner = BLACK;
                            }else{
                                printf("Checkmate! White wins!\n");
                                state->winner = WHITE;
                            }
                            fflush(stdout);
                        }else{
                            state->gameOver = 1;
                            state->winner = NONE;
                            printf("Stalemate! It's a draw!\n");
                            fflush(stdout);
                        }
                    }else if(isInCheck(board, nextTurn)){
                        if(nextTurn == WHITE){
                            printf("White is in check!\n");
                        }else{
                            printf("Black is in check!\n");
                        }
                        fflush(stdout);
                    }

                }else{
                    newRow = (event->button.y / 100) + 1;
                    newCol = (event->button.x / 100) + 1;

                    if(board->squares[newRow][newCol].color != state->currentTurn){
                        state->selectedRow = -1;
                        return;
                    }
                    state->selectedRow = newRow;
                    state->selectedCol = newCol;

                    getMoves(board, state->selectedRow, state->selectedCol, &state->availableMoves, state->enPassantRow, state->enPassantCol);

                    if(state->availableMoves.count == 0){
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
    board->squares[move->targetRow][move->targetCol] = board->squares[move->currentRow][move->currentCol];

    board->squares[move->currentRow][move->currentCol].pieceType = EMPTY;
    board->squares[move->currentRow][move->currentCol].color = NONE;
}
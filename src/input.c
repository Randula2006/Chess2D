#include "../include/input.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/moves.h"
#include "../include/board.h"


void checkGameEnd(GameState * state, Board * board, PieceColor nextTurn){
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
}


void handlePromotion(SDL_Event * event, GameState * state, Board * board){
    int clickX, clickY, index;
    int choices[4] = {QUEEN, ROOK, BISHOP, KNIGHT};
    PieceColor nextTurn;

    if(event->type != SDL_MOUSEBUTTONDOWN) return;
    if(event->button.button != SDL_BUTTON_LEFT) return;

    clickX = event->button.x;
    clickY = event->button.y;

    if(clickX >= 200 && clickX <= 600 && clickY >= 350 && clickY <= 450){
        index = (clickX - 200) / 100;
        board->squares[state->promotionRow][state->promotionCol].pieceType = choices[index];
        state->pendingPromotion = 0;

        if(state->currentTurn == WHITE){
            nextTurn = BLACK;
        }else{
            nextTurn = WHITE;
        }
        state->currentTurn = nextTurn;

        checkGameEnd(state, board, nextTurn);
    }
}


void handleSelection(SDL_Event * event, GameState * state, Board * board){
    state->selectedRow = (event->button.y / 100) + 1;
    state->selectedCol = (event->button.x / 100) + 1;

    if(board->squares[state->selectedRow][state->selectedCol].color != state->currentTurn){
        state->selectedRow = -1;
        return;
    }

    int kingMoved  = (state->currentTurn == WHITE) ? state->whiteKingMoved  : state->blackKingMoved;
    int rookAMoved = (state->currentTurn == WHITE) ? state->whiteRookAMoved : state->blackRookAMoved;
    int rookHMoved = (state->currentTurn == WHITE) ? state->whiteRookHMoved : state->blackRookHMoved;


    getMoves(board, state->selectedRow, state->selectedCol, &state->availableMoves,
         state->enPassantRow, state->enPassantCol, kingMoved, rookAMoved, rookHMoved);

    if(state->availableMoves.count == 0){
        state->selectedRow = -1;
        return;
    }
}


void handleMove(SDL_Event * event, GameState * state, Board * board){
    int newRow, newCol, isValidSelection;
    PieceColor nextTurn;
    Move move;

    newRow = (event->button.y / 100) + 1;
    newCol = (event->button.x / 100) + 1;
    isValidSelection = isValidMove(&state->availableMoves, newRow, newCol);

    if(isValidSelection == 1){
        move.currentRow = state->selectedRow;
        move.currentCol = state->selectedCol;
        move.targetRow = newRow;
        move.targetCol = newCol;

        applyMove(board, &move);

        /* Check if the moved piece is King or either of the rooks. */
        if(board->squares[move.targetRow][move.targetCol].pieceType == KING){
            if(board->squares[move.targetRow][move.targetCol].color == WHITE){
                state->whiteKingMoved = 1;
            }else{
                state->blackKingMoved = 1;
            }
        }

        if(board->squares[move.targetRow][move.targetCol].pieceType == ROOK){
            if(board->squares[move.targetRow][move.targetCol].color == WHITE){
                if(move.currentRow == 8 && move.currentCol == 1){
                    state->whiteRookAMoved = 1;
                }else if(move.currentRow == 8 && move.currentCol == 8){
                    state->whiteRookHMoved = 1;
                }
            }else{
                if(move.currentRow == 1 && move.currentCol == 1){
                    state->blackRookAMoved = 1;
                }else if(move.currentRow == 1 && move.currentCol == 8){
                    state->blackRookHMoved = 1;
                }
            }
        }

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
        if(state->currentTurn == WHITE){
            nextTurn = BLACK;
        }else{
            nextTurn = WHITE;
        }
        state->currentTurn = nextTurn;

        checkGameEnd(state, board, nextTurn);

    }else{
        /* Treat as a new selection */
        if(board->squares[newRow][newCol].color != state->currentTurn){
            state->selectedRow = -1;
            return;
        }
        state->selectedRow = newRow;
        state->selectedCol = newCol;

        int kingMoved = (state->currentTurn == WHITE) ? state->whiteKingMoved : state->blackKingMoved;
        int rookAMoved = (state->currentTurn == WHITE) ? state->whiteRookAMoved : state->blackRookAMoved;
        int rookHMoved = (state->currentTurn == WHITE) ? state->whiteRookHMoved : state->blackRookHMoved;

        getMoves(board, state->selectedRow, state->selectedCol, &state->availableMoves,
                 state->enPassantRow, state->enPassantCol,
                 kingMoved, rookAMoved, rookHMoved
        );
        
        if(state->availableMoves.count == 0){
            state->selectedRow = -1;
            return;
        }
    }
}


void HandleInput(SDL_Event * event, GameState * state, Board * board){
    if(state->gameOver == 1) return;

    if(state->pendingPromotion == 1){
        handlePromotion(event, state, board);
        return;
    }

    if(event->type != SDL_MOUSEBUTTONDOWN) return;
    if(event->button.button != SDL_BUTTON_LEFT) return;

    if(state->selectedRow == -1){
        handleSelection(event, state, board);
    }else{
        handleMove(event, state, board);
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

    /* If king moved two squares it is castling -- also move the rook */
    if(board->squares[move->targetRow][move->targetCol].pieceType == KING){
        /* King side castling */
        if(move->targetCol - move->currentCol == 2){
            board->squares[move->targetRow][move->targetCol - 1] = board->squares[move->targetRow][8];
            board->squares[move->targetRow][8].pieceType = EMPTY;
            board->squares[move->targetRow][8].color = NONE;
        }
        /* Queen side castling */
        if(move->currentCol - move->targetCol == 2){
            board->squares[move->targetRow][move->targetCol + 1] = board->squares[move->targetRow][1];
            board->squares[move->targetRow][1].pieceType = EMPTY;
            board->squares[move->targetRow][1].color = NONE;
        }
    }
}
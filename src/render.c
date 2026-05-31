#include <SDL2/SDL_image.h>
#include "../include/render.h"
#include "../include/moves.h"


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
                SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
                SDL_RenderFillRect(renderer, &fillRect);

            }else{ /* White */
                SDL_SetRenderDrawColor(renderer, 238, 238, 255, 255);
                SDL_RenderFillRect(renderer, &fillRect);
            }

        }
    }
}

void load_pieces(SDL_Renderer* renderer, Textures * textures){
    textures->pieces[0][0] = IMG_LoadTexture(renderer, "assets/pawn-b.png");
    if(textures->pieces[0][0] == NULL){printf("Failed to load pawn-b.png: %s\n", IMG_GetError());}
 
    textures->pieces[1][0] = IMG_LoadTexture(renderer, "assets/pawn-w.png");
    if(textures->pieces[1][0] == NULL){printf("Failed to load pawn-w.png: %s\n", IMG_GetError());}

    textures->pieces[0][1] = IMG_LoadTexture(renderer, "assets/knight-b.png"); 
    if(textures->pieces[0][1] == NULL){printf("Failed to load knight-b.png: %s\n", IMG_GetError());}

    textures->pieces[1][1] = IMG_LoadTexture(renderer, "assets/knight-w.png");
    if(textures->pieces[1][1] == NULL){printf("Failed to load knight-w.png: %s\n", IMG_GetError());}

    textures->pieces[0][2] = IMG_LoadTexture(renderer, "assets/bishop-b.png"); 
    if(textures->pieces[0][2] == NULL){printf("Failed to load bishop-b.png: %s\n", IMG_GetError());}

    textures->pieces[1][2] = IMG_LoadTexture(renderer, "assets/bishop-w.png");
    if(textures->pieces[1][2] == NULL){printf("Failed to load bishop-w.png: %s\n", IMG_GetError());}

    textures->pieces[0][3] = IMG_LoadTexture(renderer, "assets/rook-b.png"); 
    if(textures->pieces[0][3] == NULL){printf("Failed to load rook-b.png: %s\n", IMG_GetError());}

    textures->pieces[1][3] = IMG_LoadTexture(renderer, "assets/rook-w.png");
    if(textures->pieces[1][3] == NULL){printf("Failed to load rook-w.png: %s\n", IMG_GetError());}

    textures->pieces[0][4] = IMG_LoadTexture(renderer, "assets/queen-b.png"); 
    if(textures->pieces[0][4] == NULL){printf("Failed to load queen-b.png: %s\n", IMG_GetError());}

    textures->pieces[1][4] = IMG_LoadTexture(renderer, "assets/queen-w.png");
    if(textures->pieces[1][4] == NULL){printf("Failed to load queen-w.png: %s\n", IMG_GetError());}

    textures->pieces[0][5] = IMG_LoadTexture(renderer, "assets/king-b.png"); 
    if(textures->pieces[0][5] == NULL){printf("Failed to load king-b.png: %s\n", IMG_GetError());}

    textures->pieces[1][5] = IMG_LoadTexture(renderer, "assets/king-w.png"); 
    if(textures->pieces[1][5] == NULL){printf("Failed to load king-w.png: %s\n", IMG_GetError());}


}


void render_pieces(Board * board, Textures * textures, SDL_Renderer* renderer){
    int row, col;
    int x, y;
    SDL_Texture * image;
    Piece piece;
    SDL_Rect dstRect;

    for(row = 1; row < BOARD_SIZE; row++){
        for(col = 1; col < BOARD_SIZE; col++){
            piece = board->squares[row][col];

            if(piece.pieceType == EMPTY){
                /* Skip it as it is a normal square */
            }else{
                x = (col -1) * 100;
                y = (row -1) * 100;
                
                dstRect = (SDL_Rect){x, y, BLOCK_SIZE, BLOCK_SIZE};

                image = textures->pieces[piece.color][piece.pieceType];

                SDL_RenderCopy(renderer, image, NULL, &dstRect);
            }
            


        }
    }
}


void render_selection(SDL_Renderer * renderer, GameState * state){
    int x,y;

    if(state->selectedRow != -1){
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 255, 234, 0, 110);

        x = (state->selectedCol - 1) * BLOCK_SIZE;
        y = (state->selectedRow - 1) * BLOCK_SIZE;  

        SDL_Rect rect = (SDL_Rect){x, y, BLOCK_SIZE, BLOCK_SIZE };
        SDL_RenderFillRect(renderer, &rect);
    }
}

void render_moves(SDL_Renderer * renderer, MoveList * list){
    int i, x, y;
    if(list->count <= 0) return;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for(i = 0; i < list->count ; i++){

        SDL_SetRenderDrawColor(renderer, 255, 234, 0, 110);

        x = (list->moves[i].targetCol -1) * BLOCK_SIZE;
        y = (list->moves[i].targetRow -1) * BLOCK_SIZE;  

        SDL_Rect rect = (SDL_Rect){x, y, BLOCK_SIZE, BLOCK_SIZE };
        SDL_RenderFillRect(renderer, &rect);
    }
}

void render_gameover(SDL_Renderer * renderer, GameState * state, TTF_Font * font){
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface * surface;
    SDL_Texture * texture;
    SDL_Rect dstRect;
    char * message;

    if(state->gameOver == 0) return;

    /* Dark transparent overlay over the whole board */
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 160);
    SDL_Rect overlay = {0, 0, 800, 800};
    SDL_RenderFillRect(renderer, &overlay);

    /* Pick the right message */
    if(state->winner == WHITE){
        message = "Checkmate! White wins!";
    }else if(state->winner == BLACK){
        message = "Checkmate! Black wins!";
    }else{
        message = "Stalemate! Draw!";
    }

    /* Render the text */
    surface = TTF_RenderText_Blended(font, message, white);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    /* Center the text on the board */
    dstRect.w = surface->w;
    dstRect.h = surface->h;
    dstRect.x = (800 - surface->w) / 2;
    dstRect.y = (800 - surface->h) / 2;

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_DestroyTexture(texture);
}

void render_check(SDL_Renderer * renderer, Board * board, GameState * state){
    int r, c, x, y;

    if(state->gameOver == 1) return;

    /* Find the current player's king and check if it is in check */
    for(r = 1; r < BOARD_SIZE; r++){
        for(c = 1; c < BOARD_SIZE; c++){
            if(board->squares[r][c].pieceType == KING &&
               board->squares[r][c].color == state->currentTurn){

                if(isInCheck(board, state->currentTurn)){
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 150);

                    x = (c - 1) * BLOCK_SIZE;
                    y = (r - 1) * BLOCK_SIZE;

                    SDL_Rect rect = {x, y, BLOCK_SIZE, BLOCK_SIZE};
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
    }
}

void render_promotion(SDL_Renderer * renderer, GameState * state, Textures * textures){
    int i;
    SDL_Rect bgRect, pieceRect;
    /* The four pieces the player can choose -- queen, rook, bishop, knight */
    /* Index matches piece.h enum: KNIGHT=1, BISHOP=2, ROOK=3, QUEEN=4 */
    int choices[4] = {QUEEN, ROOK, BISHOP, KNIGHT};
    int color;

    if(state->pendingPromotion == 0) return;

    color = state->currentTurn;

    /* Draw a dark background box in the center -- 4 squares wide, 1 square tall */
    bgRect = (SDL_Rect){200, 350, 400, 100};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 220);
    SDL_RenderFillRect(renderer, &bgRect);

    /* Draw each piece image inside the box */
    for(i = 0; i < 4; i++){
        pieceRect = (SDL_Rect){200 + (i * 100), 350, BLOCK_SIZE, BLOCK_SIZE};
        SDL_RenderCopy(renderer, textures->pieces[color][choices[i]], NULL, &pieceRect);
    }
}

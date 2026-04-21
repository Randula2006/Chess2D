
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Jouer/jouer.h"

#include <SDL.h>
#define WindowsW 800
#define WindowsH 600

/**
 * \brief Pour une clareté du code, on a décidé de crée des module .h qui ne sont pas indépendant des autres,
 * \brief avec sdl, cela devient vite compliquée à lire dans le cas contraire.
*/


int main(int argc, char **argv){
    srand( time( NULL ) );
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){ // Initialisation de la SDL (tout) | Verification des erreurs
        SDL_ExitWithError("Erreur d'initalisation de la SDL");
    };

    // Programme Principale
    // Création de la fenetre + renderer (les deux)
    if (SDL_CreateWindowAndRenderer(WindowsW, WindowsH, SDL_WINDOW_SHOWN, &window, &renderer) != 0){
        SDL_ExitWithError("Création de la fenetre et rendu impossible");
    }

    if (TTF_Init() != 0){
        SDL_ExitWithError("Erreur d'initalisation de la SDL_TTF");
    }
    menu(window, renderer);
    return 0;
}

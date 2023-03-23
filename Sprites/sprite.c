#include "sprite.h"
#include <string.h>
#include "../Display/Display.h"

Sprite_t *initSprite(SDL_Renderer *renderer, SDL_Window *win, char *path,int StartFrame, int nbFrame){
    Sprite_t *Sprites = malloc(sizeof(Sprite_t));
    
    Sprites->nbFrame = nbFrame;
    Sprites->frame = 0;

    char file [strlen(path)+strlen("999.png")];
    file[0] = '\0';
    char * number = malloc(strlen("999"));
    
    for (int i = StartFrame; i < nbFrame+StartFrame; i++)
    {
        printf("%s\n", file);
        file[0] = '\0';
        strcat(file, path);
        if (i < 10){
            strcat(file, "00");
        }else if (i < 100){
            strcat(file, "0");
        }
        sprintf(number, "%d", i);
        
        strcat(file, number);
        strcat(file, ".png");
        
        Sprites->image[i-StartFrame] = SDL_RenderTexture(renderer, win, file);
    }
    return Sprites;
}
void drawSprite(Sprite_t *sprite, SDL_Renderer *renderer, int x, int y, int w, int h){
    
    SDL_RenderImage(renderer, sprite->image[sprite->frame],  x, y, w, h, 0);
    
}

void freeSprite(Sprite_t *sprite){
    for (int i = 0; i < sprite->nbFrame; i++)
    {
        SDL_DestroyTexture(sprite->image[i]);
        
    }
    free(sprite);
}
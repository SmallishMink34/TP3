/**
 * \file sprite.h
 * \author M Moulias 
 * \brief Fichier gérant les sprites ainsi que les animations (plusieurs sprites qui défilent)
 * \version 0.1
 * \date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sdl\include\SDL.h"

#ifndef SPRITE_H
#define SPRITE_H

/**
 * \brief Structure Sprite_t
 * \brief Gere plusieurs sprites, permet de faire une animation
 */
struct Sprite{
    SDL_Texture *image[10];
    SDL_Rect rect[10];
    int frame;
    int nbFrame; // Nombre de frame de l'animation
};

typedef struct Sprite Sprite_t;

/**
 * \brief Create un Sprite_t
 * 
 * \param renderer 
 * \param win 
 * \param path 
 * \param StartFrame 
 * \param nbFrame 
 * \return Sprite_t* 
 */
Sprite_t *initSprite(SDL_Renderer *renderer, SDL_Window *win,char *path,int StartFrame, int nbFrame);
/**
 * \brief Affiche le sprite sur la fenetre
 * 
 * \param sprite 
 * \param renderer 
 * \param x 
 * \param y 
 * \param w 
 * \param h 
 */
void drawSprite(Sprite_t *sprite, SDL_Renderer *renderer, int x, int y, int w, int h);
/**
 * \brief Libere la memoire du sprite
 * 
 * \param sprite 
 */
void freeSprite(Sprite_t *sprite);

#endif
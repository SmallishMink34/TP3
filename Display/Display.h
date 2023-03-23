/**
 * \file Display.h
 * \author M Moulias 
 * \brief Fichier qui gère l'ensemble de l'affichage sur le jeu, gère SDL
 * \version 0.1
 * \date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "../Monstre/Monstre.h"
#include "../Joueur/joueurs.h"
#include "../sdl\include\SDL.h"
#include "../Item/item.h"
#ifndef DISPLAY_H
#define DISPLAY_H


/**
 * \brief Create un ElementOnMap_t
 * 
 * \param texture
 * \param x
 * \param y
 */
struct ElementOnMap{
    SDL_Texture * texture;
    int x;
    int y;
};
typedef struct ElementOnMap ElementOnMap_t;

/**
 * \brief Create un SDL_TextureMap_t
 * 
 * \param listeTexture
 * \param nbTexture
 * 
 */
struct SDL_TextureMap{
    ElementOnMap_t *listeTexture[TMAP*TMAP];
    int nbTexture;
};
typedef struct SDL_TextureMap SDL_TextureMap_t;

/**
 * \brief Create un SDL_TextureMap_t
 * 
 * \return SDL_TextureMap_t* 
 */
SDL_TextureMap_t *CreateTextureMap();

/**
 * \brief Affiche la map dans la console
 * 
 * \param monstre_list 
 * \param j 
 * \param TailleMap 
 */
void afficher(listeMst_t * monstre_list, joueur_t * j ,int TailleMap);

/**
 * \brief Affiche la map dans la console avec un zoom sur le joueur
 * 
 * \param monstre_list 
 * \param j 
 * \param TailleMap 
 */
void afficher_zoom(listeMst_t * monstre_list, joueur_t * j ,int TailleMap);

/**
 * \brief Affiche l'erreur SDL et Exit le programme
 * 
 * \param message 
 */
void SDL_ExitWithError(const char *message);

/**
 * \brief Affiche une image(texture) sur la fenetre
 * 
 * \param renderer 
 * \param texture 
 * \param x 
 * \param y 
 * \param w 
 * \param h 
 * \param angle
 */
void SDL_RenderImage(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h, int angle);

/**
 * \brief Crée une image et l'affiche sur la fenetre
 * 
 * \param renderer 
 * \param win 
 * \param path 
 * \param x 
 * \param y 
 * \param w 
 * \param h 
 */
void SDL_CreateImage(SDL_Renderer *renderer, SDL_Window *win, char *path, int x, int y, int w, int h);

/**
 * \brief Crée une texture a partir d'une image
 * 
 * \param renderer 
 * \param win 
 * \param path 
 * \return SDL_Texture* 
 */
SDL_Texture *SDL_RenderTexture(SDL_Renderer *renderer, SDL_Window *win, char *path);

/**
 * \brief Ajoute un monstre a la map
 * 
 * \param MonstreTexture 
 * \param renderer 
 * \param win 
 * \param monstre_list 
 * \param x 
 * \param y 
 * \return int* 
 */
int AjouterMonstreMap(SDL_TextureMap_t *MonstreTexture,SDL_Renderer *renderer,SDL_Window *win, listeMst_t* monstre_list, int x, int y);

/**
 * \brief Ajoute un item a la map
 * 
 * \param ItemTextureListe 
 * \param renderer 
 * \param win 
 * \param itemMap 
 * \param x 
 * \param y 
 */
int AjouterItemMap(SDL_TextureMap_t *ItemTextureListe, SDL_Renderer *renderer, SDL_Window *win, itemMapList_t *itemMap, item_t *item, int x, int y);

/**
 * \brief Supprime un monstre de la map
 * 
 * \param MonstreTexture 
 * \param renderer 
 * \param win 
 * \param monstre_list 
 * \param m 
 * \return void* 
 */
void *RemoveMonstreMap(SDL_TextureMap_t *MonstreTexture,SDL_Renderer *renderer,SDL_Window *win, listeMst_t* monstre_list, monstre_t *m);
/**
 * \brief Supprime un item de la map
 * 
 * \param ItemTextureListe
 * \param renderer
 * \param win
 * \param itemMap
 * \param item
 * \return void*
 */
void *RemoveItemMap(SDL_TextureMap_t *ItemTextureListe, SDL_Renderer *renderer, SDL_Window *win, itemMapList_t *itemMap, item_t *item);
#endif
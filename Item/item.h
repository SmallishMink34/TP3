/**
 * \file item.h
 * \author M Moulias 
 * \brief Fichier qui gère les items (Pos, listes,colision,inventaire)
 * \version 0.1
 * \date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "../sdl\include\SDL.h"
#include "../Constante.c"
#include "../Joueur/joueurs.h"
#include "../sdl/include/SDL2/SDL_ttf.h"

#ifndef Item_H
#define Item_H

/**
 * \brief Structure d'un item, gère aussi son positionnement sur la map
 * 
 * \param id
 * \param name
 * \param stock
 * \param stock_max
 * \param texture
 * \param x
 * \param y
 * 
 */
struct item {
    int id; // ID unique de l'item
    char *name; // Nom de l'item
    char *type; // Type de l'item (arme, armure, potion, etc...)
    char *file; // Nom du fichier de l'image
    int stock; // Stock de l'item
    int stock_max; // Stock max de l'item
    int damage; // Dégats de l'item
    SDL_Texture *texture; // Texture de l'item
    int x; // position sur la map
    int y;
};

typedef struct item item_t;

/**
 * \brief Structure d'une case de l'inventaire
 * 
 * \param rect Rectangle de la case
 * \param fond Texture de fond de la case
 * \param surfaceMessage Surface du texte
 * \param textureMessage Texture du texte
 */

struct caseInv{
    SDL_Rect rect;
    SDL_Rect rectText;
    SDL_Texture *fond;
    SDL_Surface *surfaceMessage;
    SDL_Texture *textureMessage;
    int id;
    item_t *item;
    int Selected;
};
typedef struct caseInv caseInv_t;

/**
 * \brief Structure de l'inventaire
 * 
 * \param items Liste d'item différents (max 10)
 * \param nb_items Nombre d'item
*/
struct inventory {
    caseInv_t *cases[10];
    SDL_Texture *fond;
    int nb_items;
};

typedef struct inventory inventory_t;

/**
 * \brief Structure de la liste des items sur la map
 * 
 * \param itemslist Liste des items sur la map
 * \param nbItem Nombre d'item sur la map
 */
struct itemMapList {
    item_t* itemslist[TMAP*TMAP];
    int nbItem;
};
typedef struct itemMapList itemMapList_t;



/**
 * \brief Create un item_t
 * 
 * \param id 
 * \param name 
 * \param stock 
 * \return item_t* 
 */
item_t *initItem(int id, char *name, int stock, char * type, char * file, int damage);

/**
 * \brief Initialise l'inventaire
 * 
 * \return inventory_t* 
 */
inventory_t *initInventory(SDL_Renderer *renderer, SDL_Window *win);

/**
 * \brief Initialise la liste des items sur la map
 * 
 * \return itemMapList_t* 
 */
itemMapList_t *initItemMapList();

/**
 * \brief Initialise une case de l'inventaire
 * 
 * \return caseInv_t* 
 */
caseInv_t *initCaseInv(int id, SDL_Renderer *renderer, SDL_Window *win, item_t *item, int x, int y);

//--------------------Fonctions d'Ajout d'item--------------------
/**
 * \brief Ajoute un item à l'inventaire
 * 
 * \param item 
 * \param stock 
 */
void ItemAddToInv(inventory_t *inv,item_t *item, int stock, TTF_Font *font, SDL_Renderer *renderer);

/**
 * \brief Retire un item de l'inventaire
 * 
 * \param item 
 * \param stock 
 */
void ItemRemoveFromInv(inventory_t *inv,item_t *item, int stock, TTF_Font *font, SDL_Renderer *renderer);

/**
 * \brief Ajoute un item à la liste des items sur la map
 * 
 * \param itemMapList 
 * \param item 
 * \param x 
 * \param y 
 * \return int 
 */
int AddItemOnMap(itemMapList_t *itemMapList, item_t *item, int x, int y);

/**
 * \brief Retire un item de la liste des items sur la map
 * 
 * \param itemMapList 
 * \param item 
 * \param x 
 * \param y 
 * \return int 0 Si l'item a été retiré, 1 sinon
 */
int RemoveItemOnMap(itemMapList_t *itemMapList, item_t *item);
/**
 * \brief Affiche l'inventaire
 * 
 * \param win
 * \param renderer
 * \param inv
 */
void afficher_inv(SDL_Window *win, SDL_Renderer *renderer, inventory_t *inv, TTF_Font *font, SDL_Color White);

/**
 * \brief Verifie si un item est autour du joueur
 * 
 * \param item 
 * \param j 
 * \return int 
 */
int itemCheckCase( item_t* item, joueur_t* j);

#endif
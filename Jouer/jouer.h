/**
 * \file jouer.c
 * \author M Moulias 
 * \brief Fichier qui gère l'ensemble de l'environement de jeu (combat, map, etc...)
 * \version 0.1
 * \date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../Joueur/joueurs.h"
#include "../Display/Display.h"
#include "../Monstre/Monstre.h"
#include "time.h"
#include <conio.h>


#ifndef Jouer_H
#define Jouer_H

/**
 * \brief Renvoie un nombre aléatoire entre a et b exclus
 * 
 * \param a 
 * \param b 
 * \return int 
 */
int random(int a, int b);

    /**
     * \brief Fonction qui permet d'attaquer un monstre
     * \param j Pointeur sur le joueur
     * \param m Pointeur sur le monstre
     * \param target 1 si le joueur attaque, 0 si le monstre attaque
     * \return 1 si le monstre/Joueur est mort, 0 sinon
     */
int attaque(joueur_t*j, monstre_t *m, int target, int BonusDamage);

/**
 * \brief Renvoie 1 si le joueur est dans la zone de clic
 * 
 * \param mousex 
 * \param mousey 
 * \param x 
 * \param y 
 * \param w 
 * \param h 
 * \return int 
 */
int betweenCoords(int mousex, int mousey, int x, int y, int w, int h);

/**
 * \brief Combat entre le joueur et le monstre
 * 
 * \param window 
 * \param renderer 
 * \param j 
 * \param m 
 * 
 * \return int 
 * \example Return 1 si le joueur est vivant, 0 si il exit via la croix, 2 si il est mort
 */
int inCombat(SDL_Window *window, SDL_Renderer *renderer, joueur_t*j, monstre_t *m);

/**
 * \brief Affiche la map avec le joueur et les monstres
 * 
 * \return int 
 */
int jouer(SDL_Window * window, SDL_Renderer * renderer);

/**
 * \brief Fais Spawn tous les éléments de la map
 * 
 * \param window 
 * \param renderer 
 * \param MonstreTextureListe 
 * \param ItemTextureListe 
 * \param itemMapList 
 * \param monstre_list 
 * 
 * \return int 0 si tout s'est bien passé, 1 sinon
 */
int SpawnAllElements(SDL_Window *window, SDL_Renderer *renderer, SDL_TextureMap_t *MonstreTextureListe, SDL_TextureMap_t *ItemTextureListe, itemMapList_t * itemMapList, listeMst_t * monstre_list);

/**
 * \brief Affiche le menu
 * 
 * \return int 
 */
int menu(SDL_Window * window, SDL_Renderer * renderer);

/**
 * \brief Affiche les règles du jeu
 * 
 * \param window 
 * \param renderer 
 * \return int 
 */
int rules(SDL_Window *window, SDL_Renderer *renderer);

#endif
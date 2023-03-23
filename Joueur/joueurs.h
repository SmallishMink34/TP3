/**
 * \file joueurs.h
 * \author M Moulias 
 * \brief Structure du joueurs
 * \version 0.1
 * \date 2023-03-02
 * \typedef joueur_t
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "../sdl\include\SDL.h"
#include "../Camera/Cam.h"
#include "../Sprites/sprite.h"


#ifndef Joueurs_H
#define Joueurs_H

/**
 * \brief Structure du joueur
 * 
 * \param pos Position du joueur
 * \param life Points de vie du joueur
 * \param maxlife Points de vie maximum du joueur
 * \param mana Points de mana du joueur
 * \param maxmana Points de mana maximum du joueur
 * \param name Nom du joueur (Aucune utilité)
 * \param attaque Attaque du joueur
 * \param texture Texture du joueur
 * 
 */

struct joueur
{
    int pos[2];
    int life;
    int maxlife;
    int mana;
    int maxmana;
    char name[20];
    int attaque;
    Sprite_t *texture;
};
typedef struct joueur joueur_t;

/**
 * \brief Deplace le joueur dans la direction souhaité (Clavier dans la console)
 * 
 * \param j 
 * \return int 
 */
int deplacement(joueur_t * j);

/**
 * \brief Création d'un joueur
 * 
 * \param x 
 * \param y 
 * \param renderer 
 * \param win 
 * \return joueur_t* 
 */
joueur_t * creationJoueur(int x, int y, SDL_Renderer * renderer, SDL_Window * win);

/**
 * \brief Affiche les informations Joueurs
 * 
 * \param j 
 * \return char* 
 */
char * toStringJr(joueur_t * j);


/**
 * \brief Modifie les points de vie du joueur
 * 
 * \param j joueur_t*
 * \param degat int 
 * \return int 
 * \retval 1 si le joueur est mort
 * \retval 0 si le joueur est vivant
 */
int lifeJoueur(joueur_t * j, int degat);

/**
 * \brief Recuperer la position du joueur
 * 
 * \param j 
 * \return int* 
 */
int *getPositionJoueur(joueur_t *j);

/**
 * \brief Recuperer la position du joueur en X
 * 
 * \param j 
 * \return int 
 */
int getPositionJoueurX(joueur_t *j);

/**
 * \brief Recuperer la position du joueur en Y
 * 
 * \param j 
 * \return int 
 */
int getPositionJoueurY(joueur_t *j);

/**
 * \brief Deplace le joueur dans la direction souhaité (Gère la camera)
 * 
 * \param j 
 * \param c 
 * \param cam 
 * \return int 
 */
int deplaceto(joueur_t * j, char c, Camera_t * cam);

#endif
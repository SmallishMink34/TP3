/**
 * \file Cam.h
 * \author M Moulias 
 * \brief Fichier qui gère la camera du jeu
 * \version 0.1
 * \date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef CAM_H
#define CAM_H

/**
 * \brief Create un Camera_t
 * 
 * \param offx
 * \param offy
 * 
 */
struct Camera {
    int offx;
    int offy;
};

typedef struct Camera Camera_t;


/**
 * \brief Create un Camera_t
 * 
 * \param offx 
 * \param offy 
 * \return Camera_t* 
 */
Camera_t* Camera_new(int offx, int offy);

/**
 * \brief Crée une camera avec les coordonnées Souhaité (ici le Joueur)
 * 
 * \param cam 
 * \param x 
 * \param y 
 */
void Camera_move(Camera_t* cam, int x, int y);

#endif
/**
 * \file Monstre.h
 * \author M Moulias 
 * \brief Fichier qui gère Les monstres (Pos, listes,colision, etc...)
 * \version 0.1
 * \date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef Monstre_H
#define Monstre_H

#include <stdio.h>
#include <stdlib.h>
#include "../Joueur/joueurs.h"
#include "../Constante.c"


struct monstre {
    int pos [2];
    int life;
    int maxlife;
    char name[20];
    int attaque;
};
typedef struct monstre monstre_t;

struct listeMst{
    monstre_t* listeM[TMAP*TMAP];
    int nbMst;

};
typedef struct listeMst listeMst_t;

/**
 * \brief Create un monstre_t
 * 
 * \return listeMst_t* 
 */
listeMst_t* creationListeM();

/**
 * \brief Ajoute un monstre dans la liste
 * 
 * \param listeM 
 * \param j_pos0 
 * \param j_pos1 
 * \return int 
 */
int ajoutMst( listeMst_t* listeM, int j_pos0, int j_pos1);

/**
 * \brief Enleve un monstre de la liste
 * 
 * \param m 
 * \param listeMonster 
 */
void enleverMst( monstre_t* m, listeMst_t* listeMonster);

/**
 * \brief Check si un monstre est dans la liste
 * 
 * \param listeM 
 * \param j_pos0 
 * \param j_pos1 
 * \return int 
 */
int checkinlist(listeMst_t* listeM, int j_pos0, int j_pos1);

/**
 * \brief Check si un monstre est autour du joueur
 * 
 * \param m 
 * \param j 
 * \return int 
 */
int checkAround( monstre_t* m, joueur_t* j);

/**
 * \brief Retourne la taille de la liste
 * 
 * \param listeM 
 * \return int 
 */
int len(listeMst_t* listeM);

/**
 * \brief Affiche un monstre
 * 
 * \param M 
 * \return char* 
 */
char* toStringMst(monstre_t* M);

// char* toStringLstMst(listeMst* listeM);


#endif
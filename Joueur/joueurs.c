#include "joueurs.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "../Display/Display.h"
#include "../Constante.c"
#include "../Camera/Cam.h"
#include "../Sprites/sprite.h"

int deplacement(joueur_t * j){
    char c;
    printf("Entre une touche pour vous deplacer : ");
    c = getch();
    
    printf("\n");
    switch(c){
        case 'z':
            j->pos[1]--;
            return 1;
        case 'q':
            j->pos[0]--;
            return 1;
        case 's':
            j->pos[1]++;
            return 1;
        case 'd':
            j->pos[0]++;
            return 1;
        default:
            printf("Touche non valide");
            return 0;
    }
}


int deplaceto(joueur_t * j, char c, Camera_t * cam){
    switch(c){
        case 'z':
            if (j->pos[1] > 0){
                j->pos[1]--;
                j->texture->frame = 1;
                if (getPositionJoueurY(j) > (int)WindowsH/(TAILLE_CASE*2)-1 && getPositionJoueurY(j) < TMAP - (int)(WindowsH/(TAILLE_CASE*2))) 
                    Camera_move(cam, 0, 1);
                return 1;
                
            } else {
                return 0;
            }
        case 'q':
            if (j->pos[0] > 0){
                j->pos[0]--;
                j->texture->frame = 0;
                if (getPositionJoueurX(j) > (int)WindowsW/(TAILLE_CASE*2)-1 && getPositionJoueurX(j) < TMAP - (int)(WindowsW/(TAILLE_CASE*2))) 
                    Camera_move(cam, 1, 0);
                return 1;
            } else {
                return 0;
            }
        case 's':
            if (getPositionJoueurY(j) < TMAP){
                j->pos[1]++;
                j->texture->frame = 2;
                if (getPositionJoueurY(j) > (int)WindowsH/(TAILLE_CASE*2) && getPositionJoueurY(j) <= TMAP - (int)(WindowsH/(TAILLE_CASE*2))) 
                    Camera_move(cam, 0, -1);

                return 1;
            } else {
                return 0;
            }
        case 'd':
            if (getPositionJoueurX(j) < TMAP){
                j->pos[0]++;
                j->texture->frame = 3;
                if (getPositionJoueurX(j) > (int)(WindowsW/(TAILLE_CASE*2)) && getPositionJoueurX(j) <= TMAP - (int)(WindowsW/(TAILLE_CASE*2))) // Si le joueur peut deplacer la camera ou non
                    Camera_move(cam, -1, 0);
                return 1;
            } else {
                return 0;
            }
        default:
            printf("Touche non valide");
            return 0;
    }
}

joueur_t * creationJoueur(int x, int y, SDL_Renderer * renderer, SDL_Window * win){
    joueur_t * j = malloc(sizeof(joueur_t));
    j->pos[0] = x;
    j->pos[1] = y;
    j->life = 100;
    j->maxlife = 100;
    j->maxmana = 100;
    j->mana = 100;
    j->attaque = 10;
    j->texture = initSprite(renderer, win, "src/image/characters/player/walk/tile", 114,4); // Animation de marche dans les 4 sens
    
    return j;
}

/**
 * \brief Affiche les informations du joueur
 * 
 * \param j 
 * \return char* 
 * \example "Joueur en position (2, 1) avec 100 points de vie\n"
 */
char * toStringJr(joueur_t *j){
    printf("Joueur en position (%d, %d) avec %d points de vie\n", j->pos[0], j->pos[1], j->life);
}

int lifeJoueur(struct joueur *j, int degat){
    j->life -= degat;
    if(j->life <= 0){
        return 1;
    }
    return 0;
}

int *getPositionJoueur(joueur_t *j){
    return j->pos;
}

int getPositionJoueurX(joueur_t *j){
    return j->pos[0];
}
int getPositionJoueurY(joueur_t *j){
    return j->pos[1];
}
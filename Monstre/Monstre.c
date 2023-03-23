#include <stdio.h>
#include <stdlib.h>
#include "Monstre.h"


listeMst_t* creationListeM(){
    listeMst_t * m = malloc(sizeof(listeMst_t));
    m->nbMst = 0;
    
    return m;
}

int ajoutMst( listeMst_t* listeMonster, int j_pos0, int j_pos1){
    monstre_t * m = malloc(sizeof(monstre_t));
    m->pos[0] = j_pos0;
    m->pos[1] = j_pos1;
    m->life = 100;
    m->maxlife = 100;
    m->attaque = 10;
    for (int i = 0; i < listeMonster->nbMst; i++){
        if ((listeMonster->listeM[i]->pos[0]==j_pos0)&&(listeMonster->listeM[i]->pos[1]==j_pos1)){
            free (m);
            return 1; // Monstre Déja présent dans cette case
        }
    }
    listeMonster->listeM[listeMonster->nbMst] = m;
    listeMonster->nbMst++;

    return 0;
}

int len(listeMst_t* listeM){
    return listeM->nbMst;
}

void enleverMst( monstre_t* m, listeMst_t* listeMonster){
    int posx = m->pos[0];
    int posy =m->pos[1];
    int move = 0;
    int i = 0;
    while(i < len(listeMonster)){
        if (((listeMonster->listeM[i]->pos[0]==posx)&&(listeMonster->listeM[i]->pos[1]==posy))||(move == 1)){
            move = 1;
            listeMonster->listeM[i] = listeMonster->listeM[i+1];
        }
        i++;
    }
    listeMonster->nbMst--;
}

int checkinlist(listeMst_t* listeMonster, int j_pos0, int j_pos1){
    int i = 0;
    while(i < len(listeMonster)){
        if ((listeMonster->listeM[i]->pos[0]==j_pos0)&&(listeMonster->listeM[i]->pos[1]==j_pos1)){
            return 1;
        }
        i ++;
    }
    return 0;
}

// fonction qui recherche un joueur sur le monstre
int checkAround( monstre_t* m, joueur_t* j){
    int posx = m->pos[0];
    int posy =m->pos[1];
    if ((j->pos[0]==posx)&&(j->pos[1]==posy)){
        return 1;
    }
    return 0;
}

char* toStringMst(monstre_t* M) {
    printf("Monstre en position (%d,%d) avec %d points de vie", M->pos[0], M->pos[1], M->life);

}
#define SDL_MAIN_HANDLED  
#include "../Monstre/Monstre.h"


void main(){
    listeMst_t* listeMonster = creationListeM();
    ajoutMst(listeMonster, 0, 0);
    
    monstre_t* m = listeMonster->listeM[0];
    
    printf("len(listeMonster) = %d)\n", len(listeMonster));
    if (ajoutMst(listeMonster, 0, 0) == 1){
        printf("Monstre Déja présent dans cette case\n");
    }
    
    ajoutMst(listeMonster, 1, 1);
    printf("len(listeMonster) = %d)\n", len(listeMonster));
    enleverMst(m, listeMonster);
    printf("len(listeMonster) = %d)\n", len(listeMonster));

    for (int i = 0; i < len(listeMonster); i++){
        toStringMst(listeMonster->listeM[i]);
    }
    
}
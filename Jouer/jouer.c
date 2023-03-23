
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jouer.h"
#include "../sdl\include\SDL.h"
#include "../Display/Display.h"
#include "../sdl/include/SDL2/SDL_ttf.h"
#include "../Constante.c"
#include "../Camera/Cam.h"
#include "../Sprites/sprite.h"
#include "../Item/item.h"


int random (int a, int b){
    return rand()%(b-a) + a;
}

int betweenCoords(int mousex, int mousey, int x, int y, int w, int h){
    if (mousex >= x && mousex <= x+w && mousey >= y && mousey <= y+h) return 1;
    return 0;
}

int attaque(joueur_t*j, monstre_t *m, int target, int BonusDamage){
    if (target == 1){
        m->life -= j->attaque + BonusDamage;

        if (m->life <= 0){
            m->life = 0;
            return 1;
        }
    }else{
        j->life -= m->attaque + BonusDamage;
        if (j->life <= 0){ 
            j->life = 0;
            return 1;
        }
    }
    return 0;
}

int inCombat(SDL_Window *window, SDL_Renderer *renderer, joueur_t*j, monstre_t *m){
    char choice;
    int mchoice;
    int Start = SDL_TRUE;
    int ForceEnd = 0;
    
    int counter = 0; // Compteur pour l'animation (Joueur & Monstre)
    int oldcounter = 0; // Ancien compteur pour l'animation
    int loopCounter = 0; // Compteur pour l'animation (Monstre)
    int oldloopCounter = 0; // Ancien compteur pour l'animation
    int time = 0;
    
    int PremierPhase = 0;
    int DeuxiemePhase = 0;


    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = WindowsW;
    rect.h = WindowsH;
    
    SDL_Texture *Background = SDL_RenderTexture(renderer, window, "src\\image\\Images\\background.jpg");
    SDL_Texture *Background_Victoire = SDL_RenderTexture(renderer, window, "src\\image\\Images\\background-combat-victoire.png");
    SDL_Texture *Background_Defaite = SDL_RenderTexture(renderer, window, "src\\image\\Images\\background-combat-defaite.png");
    SDL_Texture *Combat = SDL_RenderTexture(renderer, window, "src\\image\\Images\\background-combat.png");
    // Changer la couleur du rectangle
    SDL_SetRenderDrawColor(renderer, 0, 80, 0, 255); // Noir

    // Generation Texture Joueur
    Sprite_t *idle = initSprite(renderer, window, "src/image/characters/player/Attaque/tile", 0, 1); // Joueur
    Sprite_t *attaque1 = initSprite(renderer, window, "src/image/characters/player/Attaque/tile", 0, 6);
    // Rectangle Joueur
    SDL_Rect rectJ; // Rectangle de vie
    rectJ.x = 20;
    rectJ.y = 20;
    rectJ.w = (200/j->maxlife)*j->life;
    rectJ.h = 20;

    SDL_Rect rectJ2; // Rectangle de fond
    rectJ2.x = 15;
    rectJ2.y = 15;
    rectJ2.w = 210;
    rectJ2.h = 30;

    // Rectangle Mana Joueur
    j->mana = j->maxmana;
    SDL_Rect rectManaJ2; // Rectangle de fond
    rectManaJ2.x = 15;
    rectManaJ2.y = 50;
    rectManaJ2.w = 150;
    rectManaJ2.h = 30;

    SDL_Rect rectManaJ; // Rectangle de mana
    rectManaJ.x = 20;
    rectManaJ.y = 55;
    rectManaJ.w = 140;
    rectManaJ.h = 20;

    // Rectangle Vie Monstre
    SDL_Rect rectM; // Rectangle de vie
    rectM.x = 575;
    rectM.y = 20;
    rectM.w = (200/m->maxlife)*m->life;
    rectM.h = 20;

    SDL_Rect rectM2; // Rectangle de fond
    rectM2.x = 570;
    rectM2.y = 15;
    rectM2.w = 210;
    rectM2.h = 30;

    // Annimation Monstre
    Sprite_t *idleM = initSprite(renderer, window, "src/image/characters/monsters/Attaque/tile", 0, 1); // Monstre
    Sprite_t *attaque1M = initSprite(renderer, window, "src/image/characters/monsters/Attaque/tile", 0, 6); // Monstre
    int ActualSprite = 0;
    int actualSpriteM = 0;
    int playerEsquive = 0;

    int Round = 0;
    // SDL
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    
    // --------------------------------------------Boucle de combat--------------------------------------------
    while (Start){
        counter = SDL_GetTicks();
        if (Round == 1){
            loopCounter = SDL_GetTicks();
            if ((loopCounter - oldloopCounter >= 1) && PremierPhase == 0){

                if (mchoice == 1){

                    actualSpriteM = 2;
                }
                PremierPhase = 1;
            }
            
            if (loopCounter - oldloopCounter >= 600 && DeuxiemePhase == 0){
                
                if (mchoice >= 2){
                    if (playerEsquive == 0) attaque(j, m, 0, 0);
                    else playerEsquive = 0;

                    rectJ.w = (200/j->maxlife)*j->life;

                    actualSpriteM = 1;
                }
                DeuxiemePhase = 1;
            }
            if (loopCounter - oldloopCounter >= 1200){
                Round = 0;
                PremierPhase = 0;
                DeuxiemePhase = 0;
                oldloopCounter = SDL_GetTicks();
            }
            
            
        }
        // Evenements
        SDL_Event event;
        while (SDL_PollEvent(&event)){ // Evenement qui ne coupe pas le programme
            switch (event.type){
                case SDL_QUIT:
                    Start = SDL_FALSE;
                    ForceEnd = 1;
                    break;
                
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym){
                        case SDLK_SPACE:
                            if (m->life <= 0 || j->life <= 0){
                                Start = SDL_FALSE;
                                break;
                            }
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (Round == 0){
                        if (event.button.button == SDL_BUTTON_LEFT){
                            if (betweenCoords(event.button.x, event.button.y, 6, 132, 151, 55) && ActualSprite == 0){
                                mchoice = random(1, 5);
                                if (mchoice >= 2) attaque(j, m, 1, 0); // Attaque normale (25% d'échec)
                                rectM.w = (200/m->maxlife)*m->life;
                                ActualSprite = 1;
                                oldcounter = SDL_GetTicks();
                            }
                            if (betweenCoords(event.button.x, event.button.y, 6, 193, 151, 55) && j->mana > 0 && ActualSprite == 0){
                                mchoice = random(1, 5);
                                j->mana -= 20;
                                rectManaJ.w = (140/(float)j->maxmana)*j->mana;
                                if (mchoice >= 2) attaque(j, m, 1, 20); // Attaque speciale (25% d'échec)
                                rectM.w = (200/m->maxlife)*m->life;
                                ActualSprite = 1;
                                oldcounter = SDL_GetTicks();
                            }
                            if (betweenCoords(event.button.x, event.button.y, 6, 254, 151, 55) && ActualSprite == 0){
                                mchoice = random(1, 5);
                                playerEsquive = 1;
                                ActualSprite = 1;
                                oldcounter = SDL_GetTicks();
                            }
                            // Affiche la position du clic
                        }
                    }
                    break;
            }
        }
        
        if (ActualSprite == 1){ // Animation attaque joueur
            if (counter - oldcounter > 125) {

                if (attaque1->nbFrame > attaque1->frame+1){
                    attaque1->frame++;
                }
                else {
                    ActualSprite = 0;
                    attaque1->frame = 0;
                    Round = 1;
                    oldloopCounter = SDL_GetTicks();
                }
                oldcounter = counter;
            }
        }

        if (actualSpriteM == 1){ // Animation attaque monstre
            if (counter - oldcounter > 125) {

                if (attaque1M->nbFrame > attaque1M->frame+1){
                    attaque1M->frame++;
                }
                else {
                    actualSpriteM = 0;
                    attaque1M->frame = 0;
                }
                oldcounter = counter;
            }
        }

            if (counter - oldcounter >= 67){
        if (actualSpriteM == 2){ // Animation attaque monstre
                if (attaque1M->nbFrame > attaque1M->frame+1){
                    attaque1M->frame++;
                }
                else {
                    actualSpriteM = 0;
                    attaque1M->frame = 0;
                }
                oldcounter = counter;
            }
        }
        // Affichage

        if (j->life > 0 && m->life > 0){

            SDL_RenderCopy(renderer, Background, NULL, NULL); // Affiche le fond d'écran
            if (Round == 0) SDL_RenderCopy(renderer, Combat, NULL, NULL); // Affiche la barre d'action
            
            if (ActualSprite == 0){ // Affiche le sprite du joueur
                drawSprite(idle, renderer, 70, 300, 320, 320);
            }else if (ActualSprite == 1){ // Affiche l'animation d'attaque du joueur
                drawSprite(attaque1, renderer, 70, 300, 320, 320);
            }
            
            if (actualSpriteM == 0) drawSprite(idleM, renderer, 500, 300, 320, 320); // Affiche le sprite du monstre
            else if (actualSpriteM == 1) drawSprite(attaque1M, renderer, 500, 300, 320, 320); // Affiche l'animation d'attaque du monstre
            else if (actualSpriteM == 2) drawSprite(attaque1M, renderer, 500, 300, 320, 320); // Affiche l'animation d'attaque du monstre
            
            //Afficher le rectangle
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
            SDL_RenderFillRect(renderer, &rectJ2); // Rectangle Blanc (vie max)
            SDL_RenderFillRect(renderer, &rectManaJ2); // Rectangle Blanc (mana max)
            SDL_RenderFillRect(renderer, &rectM2); // Rectangle Blanc (vie max Monstre)

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rectangle rouge (vie)
            SDL_RenderFillRect(renderer, &rectJ);
            SDL_RenderFillRect(renderer, &rectM);

            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Rectangle Bleu (Mana)
            SDL_RenderFillRect(renderer, &rectManaJ);

            
        }else{
            if (m->life > 0 && j->life <= 0){
                SDL_RenderCopy(renderer, Background_Defaite, NULL, NULL); // Affiche le fond d'écran
            }else{
                SDL_RenderCopy(renderer, Background_Victoire, NULL, NULL); // Affiche le fond d'écran
            }
        }
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(10);
        

    }
    freeSprite(idle);
    freeSprite(attaque1);
    freeSprite(idleM);
    freeSprite(attaque1M);

    SDL_DestroyTexture(Background);
    SDL_DestroyTexture(Combat);
    if (Start == SDL_FALSE && ForceEnd == 1){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }else{
        
        return 1;
    }
}

void SpawnAllElements(SDL_Window *window, SDL_Renderer *renderer, SDL_TextureMap_t *MonstreTextureListe, SDL_TextureMap_t *ItemTextureListe, itemMapList_t * itemMapList, listeMst_t * monstre_list){
    // Ajout des différents Elements sur la map
    int error;
    for (int i = 0; i < random(10,15); i++){
        do{
            error = AjouterMonstreMap(MonstreTextureListe, renderer, window, monstre_list, random(0, TMAP), random(0, TMAP));
        }while (error == 1);
    }

    item_t *item;
    item_t *Potion = initItem(1, "Potion", 1,"Potion", "src\\image\\item\\Potion.png", 0);
    item_t *sword = initItem(2, "Sword", 1,"Weapon", "src\\image\\item\\sword1.png", 10);
    item_t *sword2 = initItem(3, "Sword2", 1,"Weapon", "src\\image\\item\\sword2.png", 20);
    
    for (int i = 0; i < 4; i++){
        do{
            switch (random(0, 3)){
                case 0:
                    item = Potion;
                    break;
                case 1:
                    item = sword;
                    break;
                case 2:
                    item = sword2;
                    break;

            }
            
            error = AjouterItemMap(ItemTextureListe, renderer, window, itemMapList, item,random(0, TMAP), random(0, TMAP));
        }while (error == 1);
    }
    
}

int jouer(SDL_Window *window, SDL_Renderer *renderer){
    // Declaration des variable (structure)
    listeMst_t * monstre_list = creationListeM(); // Création de la liste de monstre
    itemMapList_t * itemMapList = initItemMapList(); // Création de la liste d'item sur la map 
    joueur_t * j = creationJoueur(TMAP/2, TMAP/2, renderer, window); // Création du joueur
    monstre_t * monstreInCombat = NULL;// Création du monstre en combat
    Camera_t *cam = Camera_new(getPositionJoueurX(j), getPositionJoueurY(j)); // Création de la caméra
    inventory_t *InventaireJoueur = initInventory(renderer, window); // Création de l'inventaire du joueur

    TTF_Font* font24 = TTF_OpenFont("src/font/arial.ttf", 24);
    TTF_Font* font12 = TTF_OpenFont("src/font/arial.ttf", 12);
    SDL_Color White = {255, 255, 255};

    if(font24 == NULL) { // Si la police n'a pas pu être chargée
        fprintf(stderr, "Erreur de chargement de la police : %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    int InventaireVisible = 0; // Booléen qui gère l'affichage de l'inventaire

    SDL_RenderClear(renderer); // Vide l'affichage avant de commencer
    SDL_RenderPresent(renderer); // Affiche l'écran

    // Background;
    SDL_Texture *texture = SDL_RenderTexture(renderer, window, "src/image/path/path1.png");
    SDL_Texture *texture2 = SDL_RenderTexture(renderer, window, "src/image/path/path2.png");
    SDL_Texture *texture3 = SDL_RenderTexture(renderer, window, "src/image/path/path3.png");
    SDL_Texture *texture4 = SDL_RenderTexture(renderer, window, "src/image/path/path4.png");
    SDL_Texture *texture5 = SDL_RenderTexture(renderer, window, "src/image/path/path5.png");
    int tableauRandomAngle[TMAP][TMAP];
    int tableauRandom[TMAP][TMAP];

     // Tableau de la carte aléatoire
    for (int i = 0; i < TMAP; i++){
        for (int j = 0; j < TMAP; j++){
            tableauRandom[i][j] = random(0, 5); // Aléatoire entre les texture des chemins
            tableauRandomAngle[i][j] = random(0, 4); // 0 = 0°, 1 = 90°, 2 = 180°, 3 = 270°
        }
    }

    // Liste des texture a render
    SDL_TextureMap_t *MonstreTextureListe = CreateTextureMap(); // Texture a Render
    SDL_TextureMap_t *ItemTextureListe = CreateTextureMap(); // Texture a Render

    SpawnAllElements(window, renderer, MonstreTextureListe, ItemTextureListe, itemMapList, monstre_list);

    // Texte nombre de monstre
    SDL_Texture *texte = NULL;
    SDL_Surface *surfaceMessage = NULL;

    char nombreMonstre[50];

    sprintf(nombreMonstre, "Nombre de monstre : %d", MonstreTextureListe->nbTexture);
    printf("%s", nombreMonstre);
    surfaceMessage = TTF_RenderText_Solid(font24, nombreMonstre, White);
    texte = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    
    

    int PlayerPosX = getPositionJoueurX(j);
    int PlayerPosY = getPositionJoueurY(j);
    int PlayerCamDecalX = WindowsW/(TAILLE_CASE*2);
    int PlayerCamDecalY = WindowsH/(TAILLE_CASE*2);


    // Vie du joueur
    SDL_Rect rectJ; // Rectangle de vie
    rectJ.x = 20;
    rectJ.y = 20;
    rectJ.w = (200/j->maxlife)*j->life;
    rectJ.h = 20;

    SDL_Rect rectJ2; // Rectangle de fond
    rectJ2.x = 15;
    rectJ2.y = 15;
    rectJ2.w = 210;
    rectJ2.h = 30;

    SDL_bool Started = SDL_TRUE;
    int InCombat = 0;
    int vague = 1;

    
    while (Started){
        if (InCombat == 1){
            if (inCombat(window, renderer, j, monstreInCombat) == 1){
                RemoveMonstreMap(MonstreTextureListe, renderer, window, monstre_list, monstreInCombat);
                
                sprintf(nombreMonstre, "Nombre de monstre : %d", MonstreTextureListe->nbTexture);
                printf("%s", nombreMonstre);
                surfaceMessage = TTF_RenderText_Solid(font24, nombreMonstre, White);
                texte = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
                SDL_FreeSurface(surfaceMessage);
                InCombat = 0;
                rectJ.w = (200/j->maxlife)*j->life;
                printf("Fin du combat 1\n");
            }else{
                printf("Fin du combat\n");
                return 0;
            }
        }else{

            if (MonstreTextureListe->nbTexture == 0){
                vague++;
                SpawnAllElements(window, renderer, MonstreTextureListe, ItemTextureListe, itemMapList, monstre_list);
                return 0;
            }

            /* Evenements */
            SDL_Event event;
            while (SDL_PollEvent(&event)){ // Evenement qui ne coupe pas le programme
                switch (event.type){
                    case SDL_QUIT:
                        Started = SDL_FALSE;
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym){
                            case SDLK_ESCAPE:
                                Started = SDL_FALSE;
                                break;
                            case SDLK_z:
                                if (InventaireVisible == 0){ // Si l'inventaire n'est pas visible
                                    deplaceto(j, 'z', cam);
                                }
                                break;
                            case SDLK_s:
                                if (InventaireVisible == 0){
                                    deplaceto(j, 's', cam);

                                }
                                break;
                            case SDLK_q:
                                if (InventaireVisible == 0){
                                    deplaceto(j, 'q', cam);

                                }

                                break;
                            case SDLK_d:
                                if (InventaireVisible == 0){
                                    deplaceto(j, 'd', cam);

                                }
                                break;
                            case SDLK_e:
                                for (int i = 0; i < itemMapList->nbItem; i++){
                                    if (itemCheckCase(itemMapList->itemslist[i], j)){
                                        ItemAddToInv(InventaireJoueur, itemMapList->itemslist[i], 1, font24, renderer); // Ajoute l'item a l'inventaire
                                        RemoveItemMap(ItemTextureListe, renderer, window, itemMapList,itemMapList->itemslist[i]); // Supprime l'item de la map
                                        monstreInCombat = monstre_list->listeM[i];
                                        printf("Ajoute un item\n");
                                        break;
                                    }else{
                                        InCombat = 0;
                                    }
                                }
                                break;
                            case SDLK_i:
                                printf("Inventaire\n");
                                if (InventaireVisible == 0) InventaireVisible = 1;
                                else InventaireVisible = 0;
                                break;
                            default:
                                break;
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_RIGHT){
                            for (int indiceCase = 0; indiceCase < InventaireJoueur->nb_items; indiceCase++){ // Parcours de l'inventaire
                                if (betweenCoords(event.button.x, event.button.y, InventaireJoueur->cases[indiceCase]->rect.x, InventaireJoueur->cases[indiceCase]->rect.y, InventaireJoueur->cases[indiceCase]->rect.w, InventaireJoueur->cases[indiceCase]->rect.h)){
                                    if (strcmp(InventaireJoueur->cases[indiceCase]->item->type, "Weapon")== 0){ // Si l'item est une arme
                                        for (int i = 0; i < InventaireJoueur->nb_items; i++){ // Parcours de l'inventaire (pour enlever la selection)
                                            if (InventaireJoueur->cases[i]->Selected == 1){
                                                InventaireJoueur->cases[i]->Selected = 0;
                                                InventaireJoueur->cases[i]->fond = SDL_RenderTexture(renderer, window, "src\\image\\Images\\case.png");
                                            }
                                        }
                                        InventaireJoueur->cases[indiceCase]->Selected = 1;
                                        InventaireJoueur->cases[indiceCase]->fond = SDL_RenderTexture(renderer, window, "src\\image\\Images\\case_selected.png");
                                        if (InventaireJoueur->cases[indiceCase]->Selected == 1){
                                            j->attaque = 10 + InventaireJoueur->cases[indiceCase]->item->damage;
                                        }
                                    }else{
                                        switch (InventaireJoueur->cases[indiceCase]->item->id) // Mal fait, mais obliger par manque de temps
                                        {
                                        case 1:
                                            if (j->life < j->maxlife){ // Inutile de consommer une potion si la vie est au max
                                                j->life += 40;
                                                ItemRemoveFromInv(InventaireJoueur, InventaireJoueur->cases[indiceCase]->item, 1, font24, renderer); // Supprime l'item de l'inventaire
                                                if (j->life > j->maxlife) j->life = j->maxlife;
                                                rectJ.w = (200/j->maxlife)*j->life; // Met a jour la barre de vie
                                            }
                                            break;
                                        
                                        default:
                                            break;
                                        }
                                    }

                                }
                            }

                        }
                        break;
                    default:
                        break;
                }
            }
            
            // Calcul de la position du joueur par rapport a la caméra
            if (getPositionJoueurX(j) >= TMAP - PlayerCamDecalX){ // Calcule X
                PlayerPosX = (TMAP-(TMAP-(int)PlayerCamDecalX)-((TMAP-(int)PlayerCamDecalX)-getPositionJoueurX(j))) * TAILLE_CASE; // Calcule du décalage a droite pour la caméra
            }else if (getPositionJoueurX(j) > PlayerCamDecalX){
                PlayerPosX = PlayerCamDecalX * TAILLE_CASE;
            }else{
                PlayerPosX = getPositionJoueurX(j) * TAILLE_CASE;
            }

            if (getPositionJoueurY(j) >= TMAP - PlayerCamDecalY){ // Caclule Y
                PlayerPosY = (TMAP-(TMAP-(int)PlayerCamDecalY)-((TMAP-(int)PlayerCamDecalY)-getPositionJoueurY(j))) * TAILLE_CASE; // Calcule du décalage en bas pour la caméra
            }else if (getPositionJoueurY(j) > PlayerCamDecalY){
                PlayerPosY = PlayerCamDecalY * TAILLE_CASE;
            }else{
                PlayerPosY = getPositionJoueurY(j) * TAILLE_CASE;
            }
            // -------------------------------------------------------
            // ------------------Affichage----------------------------

            
            for (int i = 0; i < monstre_list->nbMst; i++){
                if (checkAround(monstre_list->listeM[i], j)){
                    InCombat = 1;
                    monstreInCombat = monstre_list->listeM[i];
                    break;
                }else{
                    InCombat = 0;
                }
            }

            // Generation de la map
            for (int i = 0; i <= TMAP+1; i++){ // +1 Pour gerer les bordures
                for (int i2 = 0; i2 <= TMAP+1 ; i2++){
                    switch (tableauRandom[i][i2]){
                        case 0:
                            SDL_RenderImage(renderer, texture, i*TAILLE_CASE + cam->offx*TAILLE_CASE, i2*TAILLE_CASE+cam->offy*TAILLE_CASE, TAILLE_CASE, TAILLE_CASE, tableauRandomAngle[i][i2]*90);
                            break;
                        case 1:
                            SDL_RenderImage(renderer, texture2, i*TAILLE_CASE + cam->offx*TAILLE_CASE, i2*TAILLE_CASE+cam->offy*TAILLE_CASE, TAILLE_CASE, TAILLE_CASE, tableauRandomAngle[i][i2]*90);
                            break;
                        case 2:
                            SDL_RenderImage(renderer, texture3, i*TAILLE_CASE + cam->offx*TAILLE_CASE, i2*TAILLE_CASE+cam->offy*TAILLE_CASE, TAILLE_CASE, TAILLE_CASE, tableauRandomAngle[i][i2]*90);
                            break;
                        case 3:
                            SDL_RenderImage(renderer, texture4, i*TAILLE_CASE + cam->offx*TAILLE_CASE, i2*TAILLE_CASE+cam->offy*TAILLE_CASE, TAILLE_CASE, TAILLE_CASE, tableauRandomAngle[i][i2]*90);
                            break;
                        case 4:
                            SDL_RenderImage(renderer, texture5, i*TAILLE_CASE + cam->offx*TAILLE_CASE, i2*TAILLE_CASE+cam->offy*TAILLE_CASE, TAILLE_CASE, TAILLE_CASE, tableauRandomAngle[i][i2]*90);
                            break;
                        default:
                            break;
                    }
                }
            }
            
            for (int i = 0; i < MonstreTextureListe->nbTexture; i++){ // Render des textures des monstres
                
                SDL_RenderImage(renderer, MonstreTextureListe->listeTexture[i]->texture, MonstreTextureListe->listeTexture[i]->x+ cam->offx*TAILLE_CASE, MonstreTextureListe->listeTexture[i]->y+ cam->offy*TAILLE_CASE, TAILLE_CASE, TAILLE_CASE, 0);
            }

            for (int i = 0; i < ItemTextureListe->nbTexture; i++){ // Render des textures des items
                
                SDL_RenderImage(renderer, ItemTextureListe->listeTexture[i]->texture, ItemTextureListe->listeTexture[i]->x+ cam->offx*TAILLE_CASE, ItemTextureListe->listeTexture[i]->y+ cam->offy*TAILLE_CASE, TAILLE_CASE, TAILLE_CASE, 0);
            }


            // Affichage du joueur
            drawSprite(j->texture, renderer, PlayerPosX, PlayerPosY, 64, 64);

            // Affichage de l'inventaire
            if (InventaireVisible == 1){
                afficher_inv(window, renderer, InventaireJoueur, font24, White);
            }else{
                SDL_RenderImage(renderer, texte, 350, 20, 128, 32, 0);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Rectangle rouge (vie)
                SDL_RenderFillRect(renderer, &rectJ2);
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rectangle rouge (vie)
                SDL_RenderFillRect(renderer, &rectJ);
            }

            


            SDL_RenderPresent(renderer);
        }
    }

    // Libération de la mémoire

    // Liberation des textures
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture3);
    SDL_DestroyTexture(texture4);
    SDL_DestroyTexture(texture5);

    for (int i = 0; i < ItemTextureListe->nbTexture; i++){ // Destruction des textures des items
        SDL_DestroyTexture(ItemTextureListe->listeTexture[i]->texture);
    }

    for (int i = 0; i < MonstreTextureListe->nbTexture; i++){ // Render des textures des monstres
        SDL_DestroyTexture(MonstreTextureListe->listeTexture[i]->texture);
    }

    freeSprite(j->texture);

    // Liberation des mallocs des stuctures
    free(cam);
    free(j);
    free (MonstreTextureListe);
    free(ItemTextureListe);
    free(monstre_list);
    free(InventaireJoueur);


    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    
    return 0;
}

int menu(SDL_Window *window, SDL_Renderer *renderer){
    
    if( TTF_Init() == -1 ) { 
		SDL_ExitWithError("Erreur d'initialisation de TTF_Init");
        return EXIT_FAILURE;
	}

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_bool Started = SDL_TRUE;

    SDL_Texture *texture = SDL_RenderTexture(renderer, window, "src/image/Images/background-menu.jpg");

    int mode;

    while (Started){
        /* Evenements */
        SDL_Event event;
        while (SDL_PollEvent(&event)){ // Evenement qui ne coupe pas le programme
            switch (event.type){
                case SDL_QUIT:
                    Started = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            Started = SDL_FALSE;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT && betweenCoords(event.button.x, event.button.y, 239, 138, 318, 98)){
                        Started = SDL_FALSE;
                        mode = 1;
                    }
                    if (event.button.button == SDL_BUTTON_LEFT && betweenCoords(event.button.x, event.button.y, 239, 256, 318, 98)){
                        Started = SDL_FALSE;
                        mode = 2;
                    }
                    if (event.button.button == SDL_BUTTON_LEFT && betweenCoords(event.button.x, event.button.y, 239, 373, 318, 98)){
                        Started = SDL_FALSE;
                        
                    }
                    break;
                default:
                    break;
            }
        }

        SDL_RenderImage(renderer, texture, 0, 0, WindowsW, WindowsH,0);

        SDL_RenderPresent(renderer);
    }

    switch (mode){
        case 1:
            jouer(window, renderer);
            break;
        case 2:
            rules(window, renderer);
            break;
        default:
            return 0;
            break;
    }
}

int rules(SDL_Window *window, SDL_Renderer *renderer){


    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_bool Started = SDL_TRUE;

    SDL_Texture *texture = SDL_RenderTexture(renderer, window, "src/image/Images/background-rules.jpg");

    int mode;

    while (Started){
        /* Evenements */
        SDL_Event event;
        while (SDL_PollEvent(&event)){ // Evenement qui ne coupe pas le programme
            switch (event.type){
                case SDL_QUIT:
                    Started = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            Started = SDL_FALSE;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT && betweenCoords(event.button.x, event.button.y, 12, 549, 72, 44)){
                        Started = SDL_FALSE;
                        mode = 1;
                    }
                    break;
                default:
                    break;
            }
        }

        SDL_RenderImage(renderer, texture, 0, 0, WindowsW, WindowsH,0);

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);

    switch (mode){
        case 1:
            menu(window, renderer);
            break;
        default:
            return 0;
            break;
    }
}
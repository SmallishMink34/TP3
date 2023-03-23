#include "Display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sdl/include/SDL2/SDL_image.h"
#include "../Constante.c"
#include "../Item/item.h"


SDL_TextureMap_t *CreateTextureMap(){
    SDL_TextureMap_t *texture = malloc(sizeof(SDL_TextureMap_t));
    texture->nbTexture = 0;
    return texture;
}

void afficher_zoom(listeMst_t * monstre_list, joueur_t * joueur ,int TailleMap){
    for (int i = joueur->pos[1]-(TMAP/2); i < joueur->pos[1]+(TMAP/2); i++){
        for (int j = joueur->pos[0]-(TMAP/2); j < joueur->pos[0]+(TMAP/2); j++){
            if (checkinlist(monstre_list, j, i)){
                printf("M");
            }else if(joueur->pos[0] == j && joueur->pos[1] == i){
                printf("J");
            }else{
                printf("/");
            }
        }
        printf("\n");
    }
}

void afficher(listeMst_t * monstre_list, joueur_t * joueur ,int TailleMap){

    for (int i = 0; i < TMAP; i++){
        for (int j = 0; j < TMAP; j++){
            if (checkinlist(monstre_list, j, i)){
                printf("M");
            }else if(joueur->pos[0] == j && joueur->pos[1] == i){
                printf("J");
            }else{
                printf("/");
            }
        }
        printf("\n");
    }
}


void SDL_RenderImage(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h, int angle){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}

void SDL_ExitWithError(const char *message){
    SDL_Log("%s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

SDL_Texture *SDL_RenderTexture(SDL_Renderer *renderer, SDL_Window *win, char *path){
    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;

    //Recherche un mot dans le lien
    if (strstr(path, "png") != NULL) {
        image = IMG_Load(path);
    }else if(strstr(path, "jpg") != NULL){
        image = IMG_Load(path);
    }else{
        image = SDL_LoadBMP(path);
    }
    if (image == NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        printf("%s%s", SDL_GetBasePath(), path);
        SDL_ExitWithError("Erreur de chargement de l'image");
    }

    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    if (texture == NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_ExitWithError("Erreur de création de la texture");
    }
    return texture;
}

void SDL_CreateImage(SDL_Renderer *renderer, SDL_Window *win, char *path, int x, int y, int w, int h){
    SDL_Texture *texture = NULL;
    texture = SDL_RenderTexture(renderer, win, path);
    SDL_RenderImage(renderer, texture, x, y, w, h, 0);
    SDL_DestroyTexture(texture);
}

int AjouterMonstreMap(SDL_TextureMap_t *MonstreTexture,SDL_Renderer *renderer,SDL_Window *win, listeMst_t* monstre_list, int x, int y){
    ElementOnMap_t *monstre = malloc(sizeof(ElementOnMap_t));
    if (ajoutMst(monstre_list, x, y) == 1){
        free (monstre);
        return 1; // Probleme Monstre Déja présent
    }
    monstre->x = x*TAILLE_CASE;
    monstre->y = y*TAILLE_CASE;
    monstre->texture = SDL_RenderTexture(renderer, win, "src/image/characters/monsters/Idle/tile003.png");
    MonstreTexture->listeTexture[MonstreTexture->nbTexture] = monstre;
    MonstreTexture->nbTexture++;
    return 0; // Aucun probleme
}

int AjouterItemMap(SDL_TextureMap_t *ItemTextureListe, SDL_Renderer *renderer, SDL_Window *win, itemMapList_t *itemMap, item_t *item, int x, int y){
    ElementOnMap_t *itemTexture = malloc(sizeof(ElementOnMap_t));
    item_t *item1 = initItem(item->id, item->name, item->stock,item->type, item->file, item->damage);
    item1->x = x;
    item1->y = y;
    item1->texture = SDL_RenderTexture(renderer, win, item1->file);
    
    if (AddItemOnMap(itemMap, item1, x, y) == 1){
        printf("Item déja présent\n");
        free(item1);
        return 1; // Probleme Item Déja présent
    }
    
    itemTexture->x = x*TAILLE_CASE;
    itemTexture->y = y*TAILLE_CASE;
    itemTexture->texture = item1->texture;
    ItemTextureListe->listeTexture[ItemTextureListe->nbTexture] = itemTexture;
    ItemTextureListe->nbTexture++;
    return 0; // Aucun probleme
}

void *RemoveMonstreMap(SDL_TextureMap_t *MonstreTexture,SDL_Renderer *renderer,SDL_Window *win, listeMst_t* monstre_list, monstre_t *m){
    for (int i = 0; i < MonstreTexture->nbTexture; i++){
        if (MonstreTexture->listeTexture[i]->x == m->pos[0]*TAILLE_CASE && MonstreTexture->listeTexture[i]->y == m->pos[1]*TAILLE_CASE){
            MonstreTexture->listeTexture[i] = MonstreTexture->listeTexture[MonstreTexture->nbTexture-1];
            MonstreTexture->nbTexture--;
            break;
        }
    }
    enleverMst(m, monstre_list);
}

void *RemoveItemMap(SDL_TextureMap_t *ItemTextureListe, SDL_Renderer *renderer, SDL_Window *win, itemMapList_t *itemMap, item_t *item){
    for (int i = 0; i < ItemTextureListe->nbTexture; i++){
        if (ItemTextureListe->listeTexture[i]->x == item->x*TAILLE_CASE && ItemTextureListe->listeTexture[i]->y == item->y*TAILLE_CASE){
            ItemTextureListe->listeTexture[i] = ItemTextureListe->listeTexture[ItemTextureListe->nbTexture-1];
            ItemTextureListe->nbTexture--;
            break;
        }
    }
    RemoveItemOnMap(itemMap, item);
}
#include "item.h"
#include "../Display/display.h"
#include "../sdl/include/SDL2/SDL_ttf.h"



item_t *initItem(int id, char *name, int stock, char * type, char *file, int damage){
    item_t *item = malloc(sizeof(item_t));
    item->id = id;
    item->stock = stock;
    item->type = type;
    item->name = name;
    item->stock_max = stock;
    item->file = file;
    item->texture = NULL;
    item->x = 0;
    item->y = 0;
    item->damage = damage;
    
    return item;
}

inventory_t *initInventory(SDL_Renderer *renderer, SDL_Window *win){
    inventory_t *inventory = malloc(sizeof(inventory_t));
    inventory->fond = SDL_RenderTexture(renderer, win, "src\\image\\Images\\background-inventaire.jpg");
    int compteur = 0;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++){
            printf("i:%d j:%d %d, %d\n", i,j,100+100 * j,100+100 * i);
            inventory->cases[compteur] = initCaseInv(i+j,renderer, win, NULL, 100+100*j, 100+100*i);
            inventory->cases[compteur]->item = NULL;
            compteur++;
        }
    }

    inventory->nb_items = 0;
    return inventory;
}

itemMapList_t *initItemMapList(){
    itemMapList_t *itemMapList = malloc(sizeof(itemMapList_t));
    itemMapList->nbItem = 0;
    return itemMapList;
}


caseInv_t *initCaseInv(int id, SDL_Renderer *renderer, SDL_Window *win, item_t *item, int x, int y){
    caseInv_t *caseInv = malloc(sizeof(caseInv_t));
    caseInv->rect.x = x;
    caseInv->rect.y = y;
    caseInv->rect.w = 80;
    caseInv->rect.h = 80;

    caseInv->rectText.x = x + 10;
    caseInv->rectText.y = y + 10;
    caseInv->rectText.w = 20;
    caseInv->rectText.h = 20;

    caseInv->id = id;
    caseInv->Selected = 0;
    caseInv->fond = SDL_RenderTexture(renderer, win, "src\\image\\Images\\case.png");
    caseInv->surfaceMessage = NULL;
    caseInv->textureMessage = NULL;
    caseInv->item = item;
    return caseInv;
}

void ItemAddToInv(inventory_t *inv, item_t *element, int stock, TTF_Font *font, SDL_Renderer *renderer){
    char str[strlen("9999")];
    SDL_Color White = {255, 255, 255};
    
    for (int i = 0; i < inv->nb_items; i++){
        
        if (inv->cases[i]->item->id == element->id){
            inv->cases[i]->item->stock += stock;
            sprintf(str, "%d", inv->cases[i]->item->stock);
            inv->cases[i]->surfaceMessage = TTF_RenderText_Solid(font, str, White);
            inv->cases[i]->textureMessage = SDL_CreateTextureFromSurface(renderer, inv->cases[i]->surfaceMessage);
            SDL_FreeSurface(inv->cases[i]->surfaceMessage);
            return;
        }
    }
    if (inv->nb_items >= 10){
        printf("Inventaire plein");
        return;
    }
    
    inv->cases[inv->nb_items]->surfaceMessage = TTF_RenderText_Solid(font, "1", White);
    inv->cases[inv->nb_items]->textureMessage = SDL_CreateTextureFromSurface(renderer, inv->cases[inv->nb_items]->surfaceMessage);
    // Détruire les surfaces
    SDL_FreeSurface(inv->cases[inv->nb_items]->surfaceMessage);

    inv->cases[inv->nb_items]->item = element;
    inv->nb_items++;
    
}

void ItemRemoveFromInv(inventory_t *inv, item_t *item, int stock, TTF_Font *font, SDL_Renderer *renderer){
    char str[strlen("9999")];
    SDL_Color White = {255, 255, 255};
    for (int i = 0; i < inv->nb_items; i++){
        if (inv->cases[i]->item->id == item->id){
            if (inv->cases[i]->item->stock - stock <= 0){
                inv->cases[i]->item->stock = 0;
                for (int i2=i; i2<inv->nb_items-1; i2++){
                    inv->cases[i2]->item = inv->cases[i2+1]->item;
                    inv->cases[i2]->textureMessage = inv->cases[i2+1]->textureMessage;
                    inv->cases[i2]->surfaceMessage = inv->cases[i2+1]->surfaceMessage;
                    inv->cases[i2]->Selected = inv->cases[i2+1]->Selected;
                    inv->cases[i2]->fond = inv->cases[i2+1]->fond;
                }
                inv->nb_items--;

                return;
            }
            sprintf(str, "%d", inv->cases[i]->item->stock - stock);
            inv->cases[i]->item->stock -= stock;
            inv->cases[i]->surfaceMessage = TTF_RenderText_Solid(font, str, White);
            inv->cases[i]->textureMessage = SDL_CreateTextureFromSurface(renderer, inv->cases[i]->surfaceMessage);
            return;
        }
    }
}



void afficher_inv(SDL_Window *win, SDL_Renderer *renderer, inventory_t *inv, TTF_Font *font, SDL_Color White){
    char *number = malloc(strlen("999"));
    SDL_RenderImage(renderer, inv->fond, 0, 0, 800, 600, 0);
    for (int i = 0; i < inv->nb_items; i++){
        number[0] = '\0';
        sprintf(number, "%d", inv->cases[i]->item->stock); // Convertir le nombre en char
        SDL_RenderImage(renderer, inv->cases[i]->fond, inv->cases[i]->rect.x, inv->cases[i]->rect.y, inv->cases[i]->rect.w, inv->cases[i]->rect.h, 0); // fond case
        SDL_RenderImage(renderer, inv->cases[i]->item->texture, inv->cases[i]->rect.x, inv->cases[i]->rect.y, inv->cases[i]->rect.w, inv->cases[i]->rect.h, 0); // item
        SDL_RenderCopy(renderer, inv->cases[i]->textureMessage, NULL, &inv->cases[i]->rectText); // nombres items
        
    }
    
}

int AddItemOnMap(itemMapList_t *itemMapList, item_t *item, int x, int y){
    for (int i = 0; i < itemMapList->nbItem; i++){
        if ((itemMapList->itemslist[i]->x==x)&&(itemMapList->itemslist[i]->y==y)){
            return 1; // Item Déja présent dans cette cases
        }
    }
    itemMapList->itemslist[itemMapList->nbItem] = item;
    itemMapList->nbItem++;
    return 0;
}

int RemoveItemOnMap(itemMapList_t *itemMapList, item_t *item){
    for (int i = 0; i < itemMapList->nbItem; i++){
        if ((itemMapList->itemslist[i]->x==item->x)&&(itemMapList->itemslist[i]->y==item->y)){
            itemMapList->itemslist[i] = itemMapList->itemslist[itemMapList->nbItem-1];
            itemMapList->nbItem--;
            return 0;
        }
    }
    return 1; // Item non présent dans cette cases
}

int itemCheckCase( item_t* item, joueur_t* j){
    
    int posx = item->x;
    int posy =item->y;
    if ((j->pos[0]==posx)&&(j->pos[1]==posy)){
        return 1;
    }
    return 0;
}
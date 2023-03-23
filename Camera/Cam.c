#include "Cam.h"
#include "../sdl/include/SDL.h"
#include "../Constante.c"

Camera_t *Camera_new(int offx, int offy){
    Camera_t* cam = malloc(sizeof(Camera_t));
    cam->offx = -offx + (int)(WindowsW/(TAILLE_CASE*2));
    if (cam->offx > 0) cam->offx = 0;
    cam->offy = -offy + (int)(WindowsH/(TAILLE_CASE*2));
    if (cam->offy > 0) cam->offy = 0;

    return cam;
}

void Camera_move(Camera_t *cam, int x, int y){

    cam->offx += x;
    cam->offy += y;
}


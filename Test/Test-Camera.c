#include "../Camera/Cam.h"

void main(){
    Camera_t *cam = Camera_new(0,0);
    printf("offx = %d, offy = %d\n", cam->offx, cam->offy);
    Camera_move(cam, 1, 1);
    printf("offx = %d, offy = %d", cam->offx, cam->offy);
}
gcc -c Joueur/joueurs.c -o Joueur/joueurs.o 
gcc -c Display/Display.c -o Display/Display.o -I sdl/include -L sdl/lib -lmingw32 -lSDL2main -lSDL2
gcc -c Monstre/Monstre.c -o Monstre/Monstre.o
gcc -c Jouer/jouer.c -o Jouer/jouer.o
gcc -c Camera/Cam.c -o Camera/Cam.o
gcc -c Sprites/sprite.c -o Sprites/Sprites.o
gcc -c Item/item.c -o Item/item.o
gcc main.c Joueur/joueurs.o Display/Display.o Monstre/Monstre.o Jouer/jouer.o Camera/Cam.o Sprites/Sprites.o Item/item.o -o main.exe -I sdl/include -L sdl/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf


gcc Test/Test-Camera.c Camera/Cam.o -o Test/Test-Camera.exe -I sdl/include -L sdl/lib -lmingw32 -lSDL2main -lSDL2
gcc Test/Test-Monstre.c Monstre/Monstre.o -o Test/Test-Monstre.exe -I sdl/include -L sdl/lib -lmingw32 -lSDL2main -lSDL2

cd Test
Test-Monstre.exe
Test-Camera.exe

cd ../
main.exe
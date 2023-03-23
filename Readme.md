
# Jeu TP3
Ce jeu est un programme C réalisant le TP3 de Méthodo 1 a la FST de Vandoeuvres-lès-Nancy.
Il a été réalisé avec SDL2.
C'est un RPG de plateau 2D.




## Les règles

Ce jeu ce joue a 1 joueur sur un plateau 2D. Le personnage spawn au milieu d'un plateau de 40 par 40 est tente de survivre le plus longtemps possible au fil des manches. 
Il est capable de se deplacer, de combattre des ennemies dans une ruelle. 
Le personnage peut récuperer des armes et des potions pour s'améliorer.



## Bibliothèques
 - Cam.h
 - Display.h
 - item.h
 - jouer.h
 - joueurs.h
 - Monstre.h
 - sdl.h
 - sprite.h


## FAQ

#### Les projet ce découpent-il en module indépendant

Non, il est bien découpée en plusieurs module, mais ils ne sont pas indépendant.
l'utilisation de SDL2 rend difficile l'utilisation de plusieurs module sans importer des fonctions et autres fichiers dans certains module.
Notament, le fichier Display.h qui est importer dans plusieurs autres modules



## Ajouts

#### SDL
L'intégralité du projet est géré avec la bibliothèque de rendu SDL2, permettant l'affichage.

#### Caméra
Le joueur se déplace sur une carte de 40x40 blocs, ainsi la caméra le suit.

#### Items
A chaque manche, la carte regénére des monstres et des items capable d'être récuperés.

#### Inventaire
Les items sont rangés les uns à la suite des autres dans l'inventaire (Key : I)
Les armes peuvent être séléctionnés, tandis que les potions peuvent être consommée.

#### Système de Combat
Le Système de combat a été modifier en implémantant un Système de Tour par tour. 
Le joueur se bat contre un ennemi dans une ruelle. Il a la capacité d'attaqué avec des armes ou en utilisant son mana. Il peut également esquiver les attaques ennemis. Néanmoins,l'ennemi est également capable d'esquiver et d'attaquer.

#### Les règles
Les règles sont ré-expliqués dans le menu "Rules".
## Authors

- [@Matthéo Moulias](https://github.com/SmallishMink34)
- @Sami Benzid

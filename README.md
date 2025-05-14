## Trailer
https://youtu.be/8M4VYbD1TSA

## Architecture du code

Main : sert à lancer le jeu

Game : crée la boucle de jeu et les classes importantes à son lancement

GameStateManager : Classe mère qui permet de gérer chaque état du jeu : Game, Pause, Preparation, TitleScreen

MainManager : gère les transitions entre les états du jeu

GameObjet : Classe mère qui implémente tous les game objet (Thief, Turret, Missile) et leurs fonctions

Animation : gère les animations

Tile : code pour créer une tile -> Va évoluer en fonction de si les tiles peuvent être utilisée par des ennemis ou non et en fonction du sprite

TileMap : la map du jeu, contient les tiles.

Player : Implémentation du joueur

core.h : Implémentation des structures de données du jeu

MathUtils.h : Fonctions et attributs pour calculs mathématiques

Vague.h : Attributs appartenant à chaque nouvelle vague du jeu

## But du jeu

Arrêter les voleurs de la banque avant qu'ils sortent. Pour cela, vous pouvez cliquer dessus ou placer des tourelles pour les stoper. Cela vous permettra de récupérer l'argent volé.
L'argent sorti est supprimé de votre compte.
Si trop d'argents sort, vous perdez !

## Set up du jeu

Pour lancer le jeu, il suffit de lancer le fichier main.cpp ou lancer le fichier x64/Release/DevelopAtUbisoft.exe

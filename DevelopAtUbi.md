##Etat du jeu

En cette première partie du programme, je n'ai pas eu l temps de beaucoup m'avancer sur le jeu dûs à deux nombreux examens et partiels dans ma formation.

Le jeu ne peut donc pas être encore jouer, il y a que les tiles qui apparaissent (et que des tiles grass car je n'ai pas encore trouvé les ressources que je souhaite).
Je m'excuse de cet avancement qui peut paraître ridicule et je me promets de redoubler d'efforts jusqu'à la fin du projet.
De plus, j'ai du m'adapté à l'environnement de C++, ce qui a compliqué mon avancement.

##Architecture du code
Main : sert à lancer le jeu
Game : crée la boucle de jeu et les classes importantes à son lancement
Tile : code pour créer une tile -> Va évoluer en fonction de si les tiles peuvent être utilisée par des ennemis ou non et en fonction du sprite
TileMap : la map du jeu, contient les tiles.

##Set up du jeu

Pour lancer le jeu, il suffit de lancer le fichier main.cpp
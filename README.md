# Cloner le fichier sur votre ordinateur
```
git clone https://github.com/JdeJo1/ProjetC
```


# Add library SDL2 dev/ttf/image
```
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

# Compile
```
make all
make Players
```
Le makefile va compiler tous les fichiers .c et .h du projet

# Usage
```
chmod +x run.sh
./run.sh
chmod +x splashmem
```
Il faut des fois augmenter les permissions d'execution du fichier run.sh et l'executable qu'il génére qui disparaissent de temps en temps.
Le ./run.sh execute cette fonction : ./splashmem ./players/p1.so ./players/p2.so ./players/p3.so ./players/p4.so il lance donc l'executable du projet avec en paramètres les différentes bibliothèques dynamiques.



# Code demandé et réalisé pour le projet : 

● Prendre en paramètre du programme les bibliothèques dynamiques.

● Rattacher la bibliothèque à un joueur du moteur.

● Récupérer les actions des joueurs (grâce à la bibliothèque)

● Altérer les propriétés des joueurs en fonction de l’action.

● Décompter les crédits des joueurs

# Code suplémentaire ajouté :

● Ajout d'une fenêtre de départ avec une image généré par IA rappelant le jeu (d'où l'importance d'installer la bilbiothèque SDL2 image).

● Ajout d'une fenêtre affichant les crédits de chaque joueurs.

● Fermeture des fenêtre quand le jeu est terminé (quand plus aucun joueur n'a de crédits)

● Ajout d'un code permettant de montrer clairement le joueur gagnant avec les différents scores à la fin de la partie.


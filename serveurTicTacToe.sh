#########
#  
# ecrit par : LOTOY BENDENGE Vianney & OUSLEYEH BILEH Yassin 
#
# Makefile pour le jeu Ultimate Tic-tac-toe
#
#########
#!/bin/bash

# si les argument sont inferieur à 1, on affiche ce message d'usage...
if [ "$#" -lt 1 ]
then
	echo "Usage : run_serveur.sh portServeur"
	exit
fi

portServeur=$1

#on lance le serveur
cd TicTacToe_Com/
make
cd bin/
#gnome-terminal -e "bash -c './Serveur_arbitre ${portServeur};bash'"


gnome-terminal -e "bash -c './tictactoeServeur ${portServeur};bash'"
cd ../..

#########
#  
# ecrit par : LOTOY BENDENGE Vianney & OUSLEYEH BILEH Yassin 
#
# Makefile pour le jeu Ultimate Tic-tac-toe
#
#########
#!/bin/bash

# si les argument sont inferieur à 4, on affiche ce message d'usage...
if [ "$#" -lt 4 ]
then
	echo "Usage : joueurTicTacToe.sh hostServeur portServeur nomJoueur portIA"
	exit
fi

hostServeur=$1
portServeur=$2
nomJoueur=$3
portIA=$4

#Path du jasper / sictus de nos ordi.
#export LD_LIBRARY_PATH=/usr/local/sicstus4.3.1/lib/ #(to comment once launched in faculty computer)
#export CLASSPATH=.:TicTacToeTenJava:/usr/local/sicstus4.3.1/lib/sicstus-4.3.1/bin/jasper.jar #(to comment for the faculty)




#Path du jasper / sicstus de la FAC
export LD_LIBRARY_PATH=/applis/sicstus-4.3.2/lib/ #(to uncomment for faculty computer)
export CLASSPATH=.:TicTacToeTenJava:/applis/sicstus-4.3.2/lib/sicstus-4.3.2/bin/jasper.jar #(to uncomment for the faculty)

#on lance le moteur IA
cd TicTacToeTenJava/
javac -d ./bin/ ./src/moteurIA/*.java
cd bin/
gnome-terminal -e "bash -c 'java moteurIA.Moteur ${portIA};bash'"
clear
sleep 1.5
cd ../..

#on lance le joueur
cd TicTacToe_Com/
make
cd bin/
gnome-terminal -e "bash -c './joueurTicTacToe ${hostServeur} ${portServeur} ${nomJoueur} ${portIA};bash'"


#########
#  
# ecrit par : LOTOY BENDENGE Vianney & OUSLEYEH BILEH Yassin 
#
# Makefile pour le jeu Ultimate Tic-tac-toe
#
#########

# For Linux

CC = gcc
CFLAGS = -c -Wall
OBJ = obj/
LIBS = -L lib/
SRC = src/
BIN = bin/
INC = -I include/
VALID = include/

all: joueurTicTacToe serveurTicTacToe


serveurTicTacToe: serveurTicTacToe.o FonctionServeur.o fonctionsTCP.o 
	$(CC) $(LIBS) -o $(BIN)serveurTicTacToe $(OBJ)serveurTicTacToe.o $(OBJ)FonctionServeur.o $(VALID)tictactoe.o  $(OBJ)fonctionsTCP.o  -lfonctionsTCP

joueurTicTacToe: joueurTicTacToe.o FonctionsJoueur.o fonctionsTCP.o
	$(CC) $(LIBS) -o $(BIN)joueurTicTacToe $(OBJ)joueurTicTacToe.o $(OBJ)FonctionsJoueur.o $(OBJ)fonctionsTCP.o  -lfonctionsTCP


FonctionsJoueur.o: $(SRC)FonctionsJoueur.c
	$(CC) $(INC) $(CFLAGS) $(SRC)FonctionsJoueur.c -o $(OBJ)FonctionsJoueur.o  
	
fonctionsTCP.o: $(SRC)fonctionsTCP.c
	$(CC) $(INC) $(CFLAGS) $(SRC)fonctionsTCP.c -o $(OBJ)fonctionsTCP.o 

FonctionServeur.o: $(SRC)FonctionServeur.c
	$(CC) $(INC) $(CFLAGS) $(SRC)FonctionServeur.c -o $(OBJ)FonctionServeur.o  
	
joueurTicTacToe.o: $(SRC)Joueur.c
	$(CC) $(INC) $(CFLAGS) $(SRC)Joueur.c -o $(OBJ)joueurTicTacToe.o 

serveurTicTacToe.o: $(SRC)Serveur_arbitre.c 
	$(CC) $(INC) $(CFLAGS) $(SRC)Serveur_arbitre.c -o $(OBJ)serveurTicTacToe.o 
		

#cleanlib:
#	rm -rf lib/*.a
	
#runjoueur:
#	clear 
#	./$(BIN)joueurTicTacToe localhost 8585 A

runservertictactoe:
#	clear
#	./$(BIN)serveurTicTacToe 8585

#	./$(BIN)tictactoeServeur 8585
	
	
cleanjoueur:
#rm *~ ; rm -i \#* ; 
	rm -rf $(BIN)joueurTicTacToe $(OBJ)*.o
	
cleanserver:
#rm *~ ; rm -i \#* ; 
	rm -rf $(BIN)serveurTicTacToe $(OBJ)*.o


debugjoueur:
	clear 
	ulimit -c unlimited
	ulimit -a unlimited
	#relance de l'app
	#$ gdb ./$(BIN)joueurTicTacToe core


debugserver:
	clear 
	ulimit -c unlimited
	ulimit -a unlimited
	#relance de l'app
	#$ gdb ./$(BIN)serveurTicTacToe core

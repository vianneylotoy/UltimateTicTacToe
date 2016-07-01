/*
 * Fichier : protocoleMoteurIA.h
 *
 * Synopsis : Structure d'echange entre le joueur et le moteur IA
 *            pour le jeu Tic-Tac-Toe
 *
 * Ecrit par : LOTOY BENDENGE Vianney & OUSLEYEH BILEH Yassin
 * Date :  17 / 03 / 16
 *************************************************************/ 

#ifndef PROTOCOLEMOTEURIA_H
#define PROTOCOLEMOTEURIA_H

#include <stdio.h>
#include "protocoleTicTacToe.h"

/* Structure d'echanges entre le joueur et le moteur IA*/
typedef struct {
	
  int token;                  /* l'entier qui garantie l'auhenticite de la connexion avec le moteur IA*/
  TypSymbol symbole_Joueur;   /* Symbole du joueur                                                    */
  
} TypItems;



#endif

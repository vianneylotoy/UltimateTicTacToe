/*
 * Fichier : FonctionServeur.h
 *
 * Synopsis : entete des Fonctions du Serveur arbitre
 *            pour le jeu Tic-Tac-Toe
 *
 * Ecrit par : LOTOY BENDENGE Vianney & OUSLEYEH BILEH Yassin
 * Date :  9 / 04 / 16
 *************************************************************/ 

#ifndef FONCTIONSSERVEUR_H
#define FONCTIONSSERVEUR_H

#include <fcntl.h> 
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
/* include socket */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <signal.h>
#include <sys/time.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "validation.h"
#include "protocoleTicTacToe.h"
#include "fonctionsTCP.h"

void signal_callback_handler(int signum);
int AttenteServeur(int sock);
TypPartieReq receptPartie(int sCom[], TypPartieReq req1, TypPartieReq req2, int iterator);
void envoiSigneJoueur(int sockCom[], TypPartieReq reqt1, TypPartieReq reqt2, int NbJ);
TypCoupReq receptCoup(int sCom[], int NumJoueurs);
void envoiCoupAdverse(int sock_arbitre, TypCoupReq reqt);
TypCoupRep validationCoupJoueur(int sCom[], int iterator, TypCoupReq prop_coup1, TypCoupReq prop_coup2);
void validiteCoupJoueur(int sCom[], int k, TypCoupRep repValCoup);

#endif

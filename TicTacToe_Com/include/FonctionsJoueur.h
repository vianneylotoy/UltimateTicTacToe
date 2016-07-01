/*
 * Fichier : FonctionsJoueur.h
 *
 * Synopsis : entete des Fonctions du Joueur
 *            pour le jeu Tic-Tac-Toe
 *
 * Ecrit par : LOTOY BENDENGE Vianney & OUSLEYEH BILEH Yassin
 * Date :  17 / 03 / 16
 *************************************************************/ 

#ifndef FONCTIONSJOUEUR_H
#define FONCTIONSJOUEUR_H

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
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "protocoleTicTacToe.h"
#include "protocoleMoteurIA.h"
#include "fonctionsTCP.h"

void signal_callback_handler(int signum);
TypPartieRep lancementPartie(int sock, TypPartieReq reqPartie);
void envoiSigneIA(int sock_ia, TypItems signe);
TypCoupReq reception_envoie_CoupIA(int ia_sock, int sock_serv);
void EnvoiCoupServeur(int sock_serv, TypCoupReq reqCoupServ);
bool Reception_ValiditeCoup_Serveur(int serveur_sock, int sock_ia);
void deroulement_Partie(int serveur_sock, int socket_ia, TypPartieRep rep);
void ReceptionTimeOut_Serveur(int socket_serv);
TypCoupReq ReceptionCoup_adversaire(int serveur_sock);
void envoiCoupAdvIA(int sockIA, TypCoupReq coupIA);
#endif

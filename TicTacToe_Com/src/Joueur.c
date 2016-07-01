/*
 * Fichier : Joueur.c
 *
 * Synopsis : Fonction principale du Joueur
 *            pour le jeu Tic-Tac-Toe
 *
 * Ecrit par : LOTOY BENDENGE Vianney & OUSLEYEH BILEH Yassin
 * Date :  17 / 03 / 16
 *************************************************************/ 

#include "FonctionsJoueur.h"

#define MAX_CH 30
#define TOKEN 2016

int main(int argc,char** argv){
	
	int sock,                   /* socket de connexion au serveur arbitre */
	    port,                   /* numero du port  serveur arbitre        */
	    portIA,                 /* numero du port  moteur IA              */
	    sock_ia;                /* socket de connexion au moteur IA       */
	
	TypPartieReq part;        	/* requete du joueur                      */
	TypPartieRep rep;			/* reponse provenant du serveur           */
	TypItems item;               /* requete au moteur IA                   */
	char* nomMachine;           /* nom de la machine                      */
	
	if(argc != 5){
		perror("Joueur: socket no port\n");
		exit(4);
	}
	
	 nomMachine = argv[1];
     port = atoi(argv[2]);
     
     part.idRequest = PARTIE;
	 part.nomJoueur[0] = '\0';
	 strcpy(part.nomJoueur, argv[3]);
     
     
     /* creation de connexion avec moteurIA */
     portIA = atoi(argv[4]);
     sock_ia = socketClient(nomMachine, portIA);
     if(sock_ia < 0)
     {
		 perror("Joueur: Erreur socket moteur ia\n");
		 exit(5);
	 }
	 
	 /* connexion au serveur arbitre */
	 sock = socketClient(nomMachine, port);
	 
	 if(sock < 0){
		perror("Joueur: Erreur socket\n");
		exit(0);
	 }
	 
	 
	 /* Demande d'une partie */
	 rep = lancementPartie(sock, part);
	 
	 /* Envoi des items au moteur IA pour authentification de la connexion */
     item.token = htonl(TOKEN);
     item.symbole_Joueur = htonl(rep.symb);
	 
	 /* Envoi du signe au moteur IA*/
	 envoiSigneIA(sock_ia, item);
     
     /* deroulement de la partie */
     deroulement_Partie(sock,sock_ia,rep);
		
	 
	 /* liberation du descripteur des fichiers et fermeture de connexion */
	 shutdown(sock,2);
	 close(sock);
	 shutdown(sock_ia,2);
	 close(sock_ia);
	
     return 0;
}

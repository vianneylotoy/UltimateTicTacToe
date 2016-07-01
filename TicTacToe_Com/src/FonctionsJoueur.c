/*
 * Fichier : FonctionsJoueur.c
 *
 * Synopsis : definition des Fonctions du Joueur
 *            pour le jeu Tic-Tac-Toe
 *
 * Ecrit par : LOTOY BENDENGE Vianney & OUSLEYEH BILEH Yassin
 * Date :  17 / 03 / 16
 *************************************************************/ 
#include "FonctionsJoueur.h"


#define TIME_MAX 6  /* duree maximum d'attente */

/*
* Fonction : signal
*
* Paramètres : 
*
* Retour : void
*
* Description : permet recuperer le signal en cas de coupure de Broken pipe
*               
*/ 
void signal_callback_handler(int signum){

    printf("signal SIGPIPE %d\n",signum);
}


/*
* Fonction : lancementPartie
*
* Paramètres :  int sock, socket de connexion
*               TypPartieReq reqPartie, requete de demande de partie
*				TypPartieRep rep, reponse du serveur
*  
* Retour : TypPartieRep
*
* Description : permet l'envoi des requetes de partie et la reception des signes du joueur
*               
*/
TypPartieRep lancementPartie(int sock, TypPartieReq reqPartie)
{
	TypPartieRep rep;
	int err;
	
	err = send(sock, &reqPartie, sizeof(TypPartieReq), 0);
		if(err <= 0)
		{
			perror("Joueur: erreur d'envoi \n");
			shutdown(sock,2);
			close(sock);
			exit(1);
		}
	
	err= recv(sock, &rep, sizeof(TypPartieRep), 0);
		if(err != sizeof(TypPartieRep))
		{
			perror("Joueur: erreur de reception\n");
			shutdown(sock,2);
			close(sock);
			exit(2);
		}
	
	if(rep.symb == CROIX && rep.err == ERR_OK)
	{
		        
		printf("Votre symbole est: x ou CROIX\n vous pouvez commencez la partie\n");
		printf("Le nom de votre adversaire est %s\n", rep.nomAdvers);
	}	    
	else if(rep.symb == ROND && rep.err == ERR_OK)
	{
		printf("Votre symbole est o ou ROND\n");
		printf("Le nom de votre adversaire est %s\n", rep.nomAdvers);
    }
	else if(rep.err == ERR_PARTIE)
	{
		 perror("Erreur sur la demande de partie\n");
		 exit(3);
	}
	else
	{   
		if(rep.err == ERR_TYP)
		{
			perror("Erreur sur le type de requete\n");
			exit(4);
	    }
	}
	return rep;
}



/*
* Fonction : envoiSigneIA
*
* Paramètres :  int sock_ia, socket de connexion au moteur IA
*				TypPartieRep signe, requete de partie
*  
* Retour : void
*
* Description : permet d'envoyer le signe du Joueur au Moteur IA
*               
*/
void envoiSigneIA(int sock_ia, TypItems signe)
{
	int err;                  /* Code de retour*/
    
    
     err = send(sock_ia, &signe.token, sizeof(int), 0);
				if(err != sizeof(int))
				{
					perror("Joueur: Echec d'envoi du signe au moteur IA\n");
					shutdown(sock_ia, 2);
					close(sock_ia);
					exit(1);
				}

	 err = send(sock_ia, &signe.symbole_Joueur, sizeof(TypSymbol), 0);
				if(err != sizeof(TypSymbol))
				{
					perror("Joueur: Echec d'envoi du signe au moteur IA\n");
					shutdown(sock_ia, 2);
					close(sock_ia);
					exit(2);
				}
}

/*
* Fonction : envoiCoupAdvIA
*
* Paramètres :  int sockIA, socket de connexion au moteur IA
*				TypCoupReq coupIA, requete du coup adverse recu
*  
* Retour : void
*
* Description : permet d'envoyer le coup de l'adversaire au Moteur IA
*               
*/
void envoiCoupAdvIA(int sockIA, TypCoupReq coupIA)
{
	int err;
	
	 coupIA.idRequest = htonl(coupIA.idRequest);
	 err = send(sockIA, &coupIA.idRequest, sizeof(TypIdRequest), 0);
     if(err != sizeof(TypIdRequest))
     {
		 perror("Joueur: erreur d'envoi de l'Idrequest de l'adverssaire vers le moteur IA\n");
		 shutdown(sockIA,2);
		 close(sockIA);
		 exit(1);
	 } 
     coupIA.symbolJ = htonl(coupIA.symbolJ);
     err = send(sockIA, &coupIA.symbolJ, sizeof(TypSymbol), 0);
     if(err != sizeof(TypSymbol))
     {
		 perror("Joueur: erreur d'envoi du  Symbol de l'adverssaire vers le moteur IA\n");
		 shutdown(sockIA,2);
		 close(sockIA);
		 exit(2);
	 }
     coupIA.pos.numPlat = htonl(coupIA.pos.numPlat);
     err = send(sockIA, &coupIA.pos.numPlat, sizeof(TypPlat), 0);
     if(err != sizeof(TypPlat))
     {
		 perror("Joueur: erreur d'envoi du Typ du SousPlateau joué par l'adverssaire vers le moteur IA\n");
		 shutdown(sockIA,2);
		 close(sockIA);
		 exit(3);
	 }
	 
     coupIA.pos.numSousPlat = htonl(coupIA.pos.numSousPlat);
     err = send(sockIA, &coupIA.pos.numSousPlat, sizeof(TypSousPlat), 0);
     if(err != sizeof(TypSousPlat))
     {
		 perror("Joueur: erreur d'envoi de la Case joué par l'adverssaire vers le moteur IA\n");
		 shutdown(sockIA,2);
		 close(sockIA);
		 exit(4);
	 }
	 
     coupIA.nbSousPlatG = htonl(coupIA.nbSousPlatG);
     err = send(sockIA, &coupIA.nbSousPlatG, sizeof(int), 0);
     if(err != sizeof(int))
     {
		 perror("Joueur: erreur d'envoi du nombre de SousPlateau Gagné joué vers le moteur IA\n");
		 shutdown(sockIA,2);
		 close(sockIA);
		 exit(5);
	 }

}



/*
* Fonction : reception_envoie_CoupIA
*
* Paramètres :  int ia_sock, socket de connexion au moteur IA
*               int sock_serv, socket de connexion au serveur arbitre 
*  
* Retour : TypCoupReq
*
* Description : permet de recevoir le coup a jouer du moteur IA.
*               
*/
TypCoupReq reception_envoie_CoupIA(int ia_sock, int sock_serv)
{
	TypCoupReq RepcoupIA;                   /* Requete de coup recu du moteur IA     */
	
	fd_set fdset;                          /* Ensemble des descripteurs des fichiers */
	int err;
	int IdRequest, symbol, numPlat, numSousPlat, nbSousPlatG;  /* initialisation a 4 octets des variables de reception des coups du moteur IA */
	
		    /*Initialisation de l'ensemble des descripteurs des fichiers */
			FD_ZERO(&fdset);
			
			/* Ajout des sockets dans l'ensemble des descripteurs des fichiers */
			FD_SET(sock_serv, &fdset);
			FD_SET(ia_sock, &fdset);
			
			/* initialisation de la taille max de l'ensemble des descripteurs des fichiers */
			int max = FD_SETSIZE;
			
			
			/* initialisation du time out pour attente de 6 secondes*/
			struct timeval tim;
			tim.tv_sec = TIME_MAX;
			tim.tv_usec = 0; 
			err = select(max, &fdset, NULL, NULL,&tim);
			
			
			/* Reception de time out du serveur si on depasse les 6 secondes*/
			 
			if(err <= 0)
			{
				ReceptionTimeOut_Serveur(sock_serv);
				exit(1);
			}

			/* detection de demande connexion s'il y a reception des coups provenant du moteur IA */
			else 
			{
				/* Reception de la structure provenant du moteur IA*/
				
					err = recv(ia_sock, &IdRequest, 4, MSG_WAITALL);
					  if(err < 4)
					  {
						 perror("Joueur: Erreur de recception IdRequest \n"); 
						 shutdown(ia_sock,2); close(ia_sock);
					  }
					 
					err = recv(ia_sock, &symbol, 4, MSG_WAITALL);
					  if(err < 4)
					  {
						 perror("Joueur: Erreur de recception du symbole \n"); 
						 shutdown(ia_sock,2); close(ia_sock);
					  }
					 
					err = recv(ia_sock, &numPlat, 4, MSG_WAITALL);
					  if(err < 4)
					  {
						 perror("Joueur: Erreur de recception numPlat \n"); 
						 shutdown(ia_sock,2); close(ia_sock);
					  }
					 
					err = recv(ia_sock, &numSousPlat, 4, MSG_WAITALL);
					  if(err < 4)
					  {
						 perror("Joueur: Erreur de recception numSousPlat \n"); 
						 shutdown(ia_sock,2); close(ia_sock);
					  }
					 
					err = recv(ia_sock, &nbSousPlatG, 4, MSG_WAITALL);
					  if(err < 4)
					  {
						 perror("Joueur: Erreur de recception nbSousPlatG \n"); 
						 shutdown(ia_sock,2); close(ia_sock);
					  }
					
					/* Affectation des valeurs dans la structure par les donnees du tableau recues du moteur IA */
					
					 RepcoupIA.idRequest = ntohl(IdRequest);     
					 RepcoupIA.symbolJ = ntohl(symbol);          
					 RepcoupIA.pos.numPlat = ntohl(numPlat);
					 RepcoupIA.pos.numSousPlat = ntohl(numSousPlat);
					 RepcoupIA.nbSousPlatG = ntohl(nbSousPlatG);
					 
					 /* Envois du coup au serveur arbitre         */
					 EnvoiCoupServeur(sock_serv, RepcoupIA);
					 
					 /* Afficahge du coup du joueur               */
					 printf(" 1 Idrequest    : %d \n",ntohl(IdRequest));
					 printf(" 2 SYmbol       : %d \n",ntohl(symbol));
					 printf(" 3 NumPlat      : %d \n",ntohl(numPlat));
					 printf(" 4 NumSousPlat  : %d \n",ntohl(numSousPlat));
					 printf(" 5 NbrSousPlat G: %d \n",ntohl(nbSousPlatG));
					
			}
		 
	return RepcoupIA;
}



/*
* Fonction : EnvoiCoupServeur
*
* Paramètres :  int sock_serv, socket de connexion au serveur arbitre
* 				TypCoupReq reqCoupIA, requete de coup recu du moteur IA au serveur
*  
* Retour : void
*
* Description : permet d'envoyer le coup recu du moteurIA au serveur
*               
*/
void EnvoiCoupServeur(int sock_serv, TypCoupReq reqCoupIA)
{
	
	int err;                         /* code de retour */
	
	/* Envoi du coup au serveur arbitre */
	
	err = send(sock_serv, &reqCoupIA, sizeof(TypCoupReq), 0);
	if(err <= 0)
	{
		perror("Joueur: Erreur d'envoi des donnees au serveur\n");
		shutdown(sock_serv,2);
		close(sock_serv);
		exit(8);
	}
	printf("Envoi du coup au serveur arbitre reussi!!!\n");
}

/*
* Fonction : ReceptionCoup_adversaire
*
* Paramètres :  int serveur_sock, socket de connexion au serveur arbitre
*  
* Retour : TypCoupReq
*
* Description : permet de recevoir le coup joue par l'adversaire du serveur arbitre 
*               
*/
TypCoupReq ReceptionCoup_adversaire(int serveur_sock)
{
	TypCoupReq Coupadv;
	int err;

	/* Reception du coup du Joueur Adverssaire */
	
		err = recv(serveur_sock, &Coupadv, sizeof(TypCoupReq),0);
		if(err != sizeof(TypCoupReq))
		{
			perror("Joueur: Echec de reception du coup de l'adversaire\n");
			shutdown(serveur_sock,2);
			close(serveur_sock);
			exit(9);
		}
	
	return Coupadv;
		
}


/*
* Fonction : Reception_ValiditeCoup_Serveur
*
* Paramètres :  int serveur_sock, socket de connexion au serveur arbitre
*  
* Retour : TypCoupRep
*
* Description : permet de recevoir les informations de validation du coup de l'adversaire
*               
*/

bool Reception_ValiditeCoup_Serveur(int serveur_sock, int sock_ia)
{
	int err;                                      /*code de retour */
	bool matchfini = false;
	TypCoupRep reponse;                          /* reponse de validation des coups */
	
	/* Reception de la validation du coup */
	
    err = recv(serveur_sock, &reponse, sizeof(TypCoupRep),0);
    if(err != sizeof(TypCoupRep))
    {
		perror("Joueur: Echec de reception de la validite du coup de l'adversaire \n");
		shutdown(serveur_sock, 2);
		close(serveur_sock);
		exit(1);
	}
	
	
	switch(reponse.err)
	{
		   case ERR_OK:
                        
						switch(reponse.validCoup)
						{
							case VALID:
							           switch(reponse.propCoup)
							           {
										   case CONT:
									                    printf("La partie continue...\n");
									                    break;
									                  
									       case GAGNANT:
									                    printf("La partie est gagnee! \n");
									                    matchfini = true;
									                    break;
									        
									       case NULLE:
									                    printf("La partie est nulle! \n");
									                    matchfini = true;
									                    break;
									                  
									       case PERDU:
									                    printf("La partie est perdue!\n");
									                    matchfini = true;
									                    break;
																  
										}
								          break;		  
								     
							case TIMEOUT:
							              printf("La partie se termine par un time out !\n");
							              break;
							              
							case TRICHE:
							              printf("La partie se termine par une triche! \n");
							              break;
						}
		                break;
		                
		   case ERR_COUP:  
		                 perror("Joueur: Erreur de reception de coup de l'adversaire \n");
		                 break;
		   
		   case ERR_TYP:
		                 perror("Joueur: Erreur de type du coup de l'adversaire \n");
		                 break;
		                 
		   default:
		                 break;
		                 
	}
	reponse.propCoup = htonl(reponse.propCoup);
	
	
	/* Envois de la reponse de validation au moteur IA */ 
	err = send(sock_ia, &reponse.propCoup, sizeof(TypCoup), 0);
     if(err != sizeof(TypCoup))
     {
		perror("Joueur: Echec d'envoi de la validite du coup de l'adversaire au moteur IA \n");
		shutdown(sock_ia, 2);
		close(sock_ia);
		exit(2);
	 }
	return matchfini;
    
}



/*
* Fonction : deroulement_Partie
*
* Paramètres :  int serveur_sock, socket de connexion au serveur arbitre
*               int socket_ia, socket de connexion au moteur IA
* 				TypPartieRep rep, reponse a la requete de demande de Partie 
*  
* Retour : void
*
* Description : permet d'assurer le deroulement de la partie
*               
*/


void deroulement_Partie(int serveur_sock, int socket_ia, TypPartieRep rep)
{
    TypCoupReq coupIA;                       /* requete de coup demande au moteur IA pour CROIX */
	       
		
		switch(rep.symb)
		{
			        
			case ROND:
						coupIA = ReceptionCoup_adversaire(serveur_sock);
						envoiCoupAdvIA(socket_ia,coupIA);
						if(Reception_ValiditeCoup_Serveur(serveur_sock,socket_ia)) break;
						
			case CROIX:
						do{
							coupIA = reception_envoie_CoupIA(socket_ia,serveur_sock);
							if(Reception_ValiditeCoup_Serveur(serveur_sock,socket_ia)) break;
							coupIA = ReceptionCoup_adversaire(serveur_sock);
							envoiCoupAdvIA(socket_ia,coupIA);
							if(Reception_ValiditeCoup_Serveur(serveur_sock,socket_ia)) break;
						}while(1);
			default:
			         break;
		}
	
	
}



/*
* Fonction : ReceptionTimeOut_Serveur
*
* Paramètres :  int socket_serv, socket de connexion au serveur arbitre
*  
* Retour : TypCoupRep
*
* Description : permet d'indiquer que le joueur a recu un time out du serveur
*               
*/
void ReceptionTimeOut_Serveur(int socket_serv)
{
	int err;
	TypCoupRep rep;
	
	err = recv(socket_serv, &rep, sizeof(TypCoupRep),0);
	if(err != sizeof(TypCoupRep))
	{
		perror("Joueur: Erreur de reception de time out serveur\n");
		shutdown(socket_serv, 2); close(socket_serv);
		
	}
	
	if(rep.validCoup == TIMEOUT)
	{
		printf("Joueur: Reception d'un time out, partie terminee! \n");
		printf("Joueur: vous avez perdu la partie! \n");
		
	}
	
}


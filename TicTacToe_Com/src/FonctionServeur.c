/*
 * Fichier : FonctionServeur.c
 *
 * Synopsis : Definition des fonctions du Serveur arbitre
 *            pour le jeu Tic-Tac-Toe
 *
 * Ecrit par : LOTOY BENDENGE Vianney & OUSLEYEH BILEH Yassin
 * Date :  9 / 04 / 16
 *************************************************************/ 
 

#include "FonctionServeur.h"
#define TIME_MAX 6  /* duree maximum d'attente */


/* capture du signal en cas "BROKEN PIPE" du Signal Handler SIGPIPE */
void signal_callback_handler(int signum){

      printf("Recuperation du signal SIGPIPE %d\n",signum);
}


/*
* Fonction : AttenteServeur
*
* Paramètres : int sock, socket de connexion
*
* Retour : int
*
* Description : permet renvoyer une valeur entiere dans les limites de temps d'attente du serveur
*               ou envoie un time out au joueur si les limites de temps d'attente sont atteintes et renvoie une valeur entiere
*               
*/
int AttenteServeur(int sock)
{
	int err;
	TypCoupRep repcoup;

    fd_set fdset;
    
			FD_ZERO(&fdset);
			FD_SET(sock, &fdset);
			int max = FD_SETSIZE;
			struct timeval tim;
			
			/* initialisation du time out pour attente de 6 secondes*/
			tim.tv_sec = TIME_MAX;
			tim.tv_usec = 0;
			err = select(max, &fdset, NULL, NULL,&tim);

			/* Envois de time out du serveur si on depasse les 6 secondes*/
			if(err <= 0)
			{
				perror("Arbitre: fin d'attente du coup du Joueur\n");
				repcoup.err = ERR_COUP;
				repcoup.validCoup = TIMEOUT;
				repcoup.propCoup = PERDU;
				err = send(sock, &repcoup, sizeof(TypCoupRep),0);
				   if(err <= 0)
				   {
					   shutdown(sock,2); close(sock);
				   }
				return 0;
			}
			else  
			{
				 return 1; 
			}

}


/*
* Fonction : receptPartie
*
* Paramètres : int sCom[], tableau des valeurs de socket de communication
* 			   TypPartieReq req1, requete de demande de partie du Joueur 1
*              TypPartieReq req2, requete de demande de partie du Joueur 2
*              int iterator, valeur d'iteration de la boucle
*
* Retour : TypPartieReq
*
* Description : permet de recevoir les requetes de demande de partie des joueurs
*               
*/

TypPartieReq receptPartie(int sCom[], TypPartieReq req1, TypPartieReq req2, int iterator)
{
	int err;                     /* code de retour */
		
			
		   if(iterator == 0)
		   {
			       /* reception de demande de partie du joueur 1 */
				   err = recv(sCom[iterator], &req1, sizeof(TypPartieReq),0);
					   if(err != sizeof(TypPartieReq))
					   {
								perror("Arbitre: erreur de reception de demande de partie du joueur 1 \n");
								shutdown(sCom[iterator], 2);
								close(sCom[iterator]);						
										
						}
				   return req1;
				   
		  }
		  
		  else
		  {
			  
		           /* reception de demande de partie du joueur 2 */
				   err = recv(sCom[iterator], &req2, sizeof(TypPartieReq),0);
					   if(err != sizeof(TypPartieReq))
					   {
								perror("Arbitre: erreur de reception de demande de partie du joueur 2\n");
								shutdown(sCom[iterator], 2);
								close(sCom[iterator]);						
						}
				   return req2;
				   
			}	   
		   
		   
}


/*
* Fonction : envoiSigneJoueur
*
* Paramètres : int sockCom[], tableau des valeurs de socket de communication
* 			   TypPartieReq reqt1, requete recu de demande de partie du joueur 1
*              TypPartieReq reqt1, requete recu de demande de partie du joueur 2
*              int NbJ, Nombre reel des joueurs connectes
*
* Retour : void
*
* Description : permet d'envoyer aux joueurs leurs signes pour le lancement de la partie
*               
*/

void envoiSigneJoueur(int sockCom[], TypPartieReq reqt1, TypPartieReq reqt2, int NbJ)
{
	TypPartieRep reponsePartie1, reponsePartie2;  /* reponse du serveur a la requete partie */
	int err,                                      /* code de retour */
	    i = 0;                                    /* iterateur de la boucle */
	
	
	printf("nouveau joueur %s \n", reqt1.nomJoueur);
	printf("nouveau joueur %s \n", reqt2.nomJoueur);
	
	while(i < NbJ)
	{
		if(i == 0)
		{
			  /* envois du signe du joueur 1 avec CROIX */
		      reponsePartie1.err = ERR_OK;
		      reponsePartie1.symb = CROIX;
		      reponsePartie1.nomAdvers[0] = '\0';
		      strcpy(reponsePartie1.nomAdvers,reqt2.nomJoueur);
		      err = send(sockCom[i], &reponsePartie1, sizeof(TypPartieRep),0);
		         if(err <= 0)
		         {
					 perror("Arbitre: erreur de reception de demande de partie du joueur 1 \n");
							int d = 0;
							for(d = 0; d < NbJ; d++)
							{
								shutdown(sockCom[d], 2);
								close(sockCom[d]);						
							}
				 }
		      
	    }
		else
		{
			  /* envois du signe du joueur 2 avec ROND */
			  reponsePartie2.err = ERR_OK;
		      reponsePartie2.symb = ROND;
		      reponsePartie2.nomAdvers[0] = '\0';
		      strcpy(reponsePartie2.nomAdvers,reqt1.nomJoueur);
		      err = send(sockCom[i], &reponsePartie2, sizeof(TypPartieRep),0);
		         if(err <= 0)
		         {
					 perror("Arbitre: erreur de reception de demande de partie du joueur 1 \n");
							int d = 0;
							for(d = 0; d < NbJ; d++)
							{
								shutdown(sockCom[d], 2);
								close(sockCom[d]);						
							}
				 }
		}
		i++;
	}
	
}



/*
* Fonction : receptCoup
*
* Paramètres : int sCom[], tableau des valeurs de socket de communication
* 			   int NumJoueurs, valeur de l'iteration de la boucle
*
* Retour : TypCoupReq
*
* Description : permet de recevoir les coups des joueurs pour le deroulement de la partie 
* 			
*/

TypCoupReq receptCoup(int sCom[], int NumJoueurs)
{
	int err;
	TypCoupReq reqCoup1, reqCoup2;
	
	
	if(NumJoueurs == 0)
	{
                    /* reception du coup du joueur 1 dans la duree de 6 secondes */
					if(AttenteServeur(sCom[NumJoueurs]) == 1)
					{
						err = recv(sCom[NumJoueurs], &reqCoup1, sizeof(TypCoupReq),0);
							if(err != sizeof(TypCoupReq))
							{
								perror("Arbitre: Erreur de reception du coup du Joueur CROIX\n");
									shutdown(sCom[NumJoueurs],2);
									close(sCom[NumJoueurs]);
							}
						printf("Arbitre: le joueur CROIX a joue le sous plateau %d \n la case %d \n et %d sous-plateaux gagnes\n"
						    , reqCoup1.pos.numPlat, reqCoup1.pos.numSousPlat, reqCoup1.nbSousPlatG);
						    

					}
					return reqCoup1;
	 }  
	 else{
		 
		            /* reception du coup du joueur 2 dans la duree de 6 secondes */
					if(AttenteServeur(sCom[NumJoueurs]) == 1)
					{
						err = recv(sCom[NumJoueurs], &reqCoup2, sizeof(TypCoupReq),0);
						   if(err != sizeof(TypCoupReq))
							{
								perror("Arbitre: Erreur de reception du coup du Joueur ROND\n");
									shutdown(sCom[NumJoueurs],2);
									close(sCom[NumJoueurs]);
							}
						printf("Arbitre: le joueur ROND a joue le sous plateau %d \n la case %d \n et %d sous-plateaux gagnes\n"
						    , reqCoup2.pos.numPlat, reqCoup2.pos.numSousPlat, reqCoup2.nbSousPlatG);

					}
		return reqCoup2;
	}
	
}


/*
* Fonction : envoiCoupAdverse
*
* Paramètres : int sock_arbitre, socket de communication
* 			   TypCoupReq reqt, requete du coup recu des joueurs
*
* Retour : void
*
* Description : permet d'envoyer les coups adverses des joueurs  
* 			
*/

void envoiCoupAdverse(int sock_arbitre, TypCoupReq reqt)
{
	int err;
	
	err = send(sock_arbitre, &reqt, sizeof(TypCoupReq),0);
	  if(err <= 0)
	  {
		  perror("Arbitre: Erreur d'envoi du coup du joueur \n");
		  shutdown(sock_arbitre,2); 
		  close(sock_arbitre);
	  }
	
}



/*
* Fonction : validationCoupJoueur
*
* Paramètres : int sCom[], tableau des valeurs de socket de communication
* 			   int iterator, iterateur de la boucle
*              TypCoupReq prop_coup1, coup recu du joueur 1
* 			   TypCoupReq prop_coup2, coup recu du joueur 2 
*
* Retour : TypCoupRep
*
* Description : permet de valider les coups des joueurs
* 			
*/

TypCoupRep validationCoupJoueur(int sCom[], int iterator, TypCoupReq prop_coup1, TypCoupReq prop_coup2)
{
	
	TypCoupRep rep_valid1, rep_valid2;             /* reponse a la requete des coups joues par le joueur 1 & joueur 2  */
	
		if(iterator == 1)
		{            
		      printf("Je suis chez valide j1\n");	        
					
			        /* validation des coups du joueur 1 */
			        if(validationCoup(iterator,prop_coup1, &rep_valid1.propCoup) == 0)
			        {
						printf("Je valide j1\n");
						rep_valid1.err = ERR_OK;
					    rep_valid1.validCoup = VALID;
					    
					}
		
					return rep_valid1;
					
		}
					
		else
		{
					
					/* validation des coups du joueur 2 */
					
			        if(validationCoup(iterator,prop_coup2, &rep_valid2.propCoup) == 0)
			        {
						rep_valid2.err = ERR_OK;
					    rep_valid2.validCoup = VALID;
					    
					}
		            
		         return rep_valid2;
		
	}
}


/*
* Fonction : validiteCoupJoueur
*
* Paramètres : int sCom[], tableau des valeurs de socket de communication
* 			   int k, iterateur de la boucle
*              TypCoupRep repValCoup, validite du coup du joueur 
*
* Retour : void
*
* Description : permet d'envoyer les informations de validations des coups adverses aux joueur 
* 			
*/

void validiteCoupJoueur(int sCom[], int k, TypCoupRep repValCoup)
{
	int err;
	
	err = send(sCom[k], &repValCoup, sizeof(TypCoupRep),0);
		if(err <= 0)
		{
			shutdown(sCom[k],2);
			close(sCom[k]);
		}
		
	printf("VALID = %d  \n",repValCoup.propCoup);
}

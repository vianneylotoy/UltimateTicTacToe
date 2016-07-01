/*
 * Fichier : Serveur_arbitre.c
 *
 * Synopsis : Fonction principale du Serveur arbitre
 *            pour le jeu Tic-Tac-Toe
 *
 * Ecrit par : LOTOY BENDENGE Vianney & OUSLEYEH BILEH Yassin
 * Date :  17 / 03 / 16
 *************************************************************/ 

#include "FonctionServeur.h"
#define MAXCl 1024

int main(int argc, char *argv[]) 
{
	int sock,                                         /* socket de connexion                                        */
	sock_trans,                                       /* socket de communication                                    */
	port,                                             /* numero du port                                             */
	maximum,                                          /* taille maximum de ensemble des descripteurs des fichiers   */
	err,                                              /* code de retour                                             */
	ncl = 0,                                          /* Nombre des clients connectes                               */    
	i = 0;                                            /* iterateur de la boucle                                     */
	int tabCl[MAXCl];                                 /* tableau des valeurs de socket de communication             */
	fd_set fd;                                        /* ensemble des descripteurs des fichiers                     */
	
	TypPartieReq partie1, partie2;                    /* requete de demande de partie                               */
	TypCoupReq coup1, coup2;                          /* requete de coup joueur                                     */
	TypCoupRep rep1,rep2;                             /*reponse de validite de coup                                 */
	
	if(argc != 2){
		perror("Arbitre: no port \n");
		exit(4);
	}
	port = atoi(argv[1]);
	sock = socketServeur(port);

	if(sock < 0)
	{
		perror("Arbitre: Erreur socket\n");
		exit(0);
	}
	printf("Starting %s on port %d with validation and timeout\n",argv[0], port);
	
    do
	{
		
		FD_ZERO(&fd);
		FD_SET(sock, &fd);
       
		for(i = 0; i < ncl; i++)
        { 
			 FD_SET(tabCl[i], &fd);
	    } 
	    
			 maximum = FD_SETSIZE;
			 err = select(maximum, &fd, NULL, NULL, NULL);
			 
			 if(err < 0)
			 {
				 perror("Serveur: erreur dans select\n");
			 }
	         	         
		   //test de demande de connexion
	       if(FD_ISSET(sock, &fd) != 0)
		   {
			   	  sock_trans = accept(sock, NULL, NULL);
			   	  		 
						 if (sock_trans < 0) {
							perror("serveurTCP:  erreur sur accept\n");
							return -5;
						 }
	             tabCl[ncl++] = sock_trans;
					 printf("Connecte\n");
				  
			
			}
	}while(i < 2);
	
		  //test de demande de communication
		   if(FD_ISSET(tabCl[i], &fd) != 0)
		   {
			   perror("Serveur: Aucun client connecte\n");
		   }
		   else
		   {			
			   /* reception des noms des joueurs pour lancement de la partie */
				i = 0;
				do
				{
				   if(i == 0)
						 partie1 = receptPartie(tabCl,partie1,partie2, i);
				   else
						 partie2 = receptPartie(tabCl,partie1,partie2, i);
				   i++;
				}while(i < ncl);
				
			   
				/* envoi du signe aux joueurs connectes */
				envoiSigneJoueur(tabCl, partie1,partie2, ncl);
	        }

	while(1)
	{
			i = 0;
			/* reception des coups des joueur et envoie des coups adverses dans les limites d'attente de 6 secondes max */
			do
			{
				
				switch(i)
				{
					case 0:
					  
							   /* Reception du coup du joueur 1 */
							   coup1 = receptCoup(tabCl,i); 
							   
							   /* Envoi du coup du joueur 1 au joueur 2 */
							   envoiCoupAdverse(tabCl[i+1],coup1);

							   /* validation des coups du joueur 1 */
							   rep1 = validationCoupJoueur(tabCl,i+1, coup1, coup2);
							   
							   /* envoi de la validite du coup du joueur 1 au joueur 1 */
							   validiteCoupJoueur(tabCl, i, rep1);
							   
							   /* envoi de la validite du coup du joueur 1 au joueur 2 */
							   validiteCoupJoueur(tabCl, i+1, rep1);
							   
							   if(rep1.propCoup == 1)
								{
									   printf("Arbitre: partie terminee, le joueur %s est gagnant \n", partie1.nomJoueur);
									   shutdown(tabCl[i], 2);
		                               close(tabCl[i]);
									   exit(1);
								}
												
								if(rep1.propCoup == 2)
								{
									   printf("Arbitre: la partie se termine par un Match Nul \n");
									   shutdown(tabCl[i], 2);
		                               close(tabCl[i]);
									   exit(3);
								}
											   
								
								 if(rep1.propCoup == 3)
								 {
									   printf("Arbitre: partie terminee, le joueur %s est perdant \n", partie1.nomJoueur);
									   shutdown(tabCl[i], 2);
		                               close(tabCl[i]);
									   exit(4);
								 }
								 
								 if(rep1.validCoup == 2)
								 {
									 printf("Arbitre: partie terminee par triche pour le joueur %s est perdant \n", partie1.nomJoueur);
									 shutdown(tabCl[i], 2);
		                             close(tabCl[i]);
									 exit(11);
								 }
			                   
			                   break;
			         
			          case 1:
			          
							   /* Reception du coup du joueur 2 */
							   coup2 = receptCoup(tabCl,i);
							   
							   /* Envoi du coup du joueur 2 au joueur 1 */
							   envoiCoupAdverse(tabCl[i-1],coup2);
							   
							   
							   /* validation du coup du joueur 2 */
							   rep2 = validationCoupJoueur(tabCl,i+1, coup1, coup2);
							   
							   /* envoi de la validite du coup du joueur 2 au joueur 2 */
							   validiteCoupJoueur(tabCl, i, rep2);
							   
							   /* envoi de la validite du coup du joueur 2 au joueur 1 */
							   validiteCoupJoueur(tabCl, i-1, rep2);
							   
							   if(rep2.propCoup == 1)
								{
									   printf("Arbitre: partie terminee, le joueur %s est gagnant \n", partie2.nomJoueur);
									   shutdown(tabCl[i], 2);
		                               close(tabCl[i]);
									   exit(5);
								}
												
								if(rep2.propCoup == 2)
								{
									   printf("Arbitre: la partie se termine par un Match Nul \n");
									   shutdown(tabCl[i], 2);
		                               close(tabCl[i]);
									   exit(6);
								}
											   
								
								 if(rep2.propCoup == 3)
								 {
									   printf("Arbitre: partie terminee, le joueur %s est perdant \n", partie2.nomJoueur);
									   shutdown(tabCl[i], 2);
		                               close(tabCl[i]);
									   exit(7);
								 }
								 
								 
								 if(rep2.validCoup == 2)
								 {
									 printf("Arbitre: partie terminee par triche pour le joueur %s est perdant \n", partie2.nomJoueur);
									 shutdown(tabCl[i], 2);
		                             close(tabCl[i]);
									 exit(9);
								 }
							   
							   break;
					
					default:
					         break;
			           
			           
			           
				}
				
				i++;
				
			}while(i < ncl);
			
	}
	
//Fermeture des sockets com et conx
	int k = 0;
	for(k = 0; k < ncl; k++)
	{
		shutdown(tabCl[k], 2);
		close(tabCl[k]);						
	}
	close(sock_trans);
	close(sock);
	
	return 0;
	
}


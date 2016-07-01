package moteurIA;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

import se.sics.jasper.SPException;

public class Moteur {

	public static void main(String[] args) {
		
		
		try {
			/* Données entrée directement*/
			if(args.length!=1) {
				   System.out.println("MoteurIA- Usage : no portIA");
				   System.exit(0);
			    }
			
			int portIA =  Integer.parseInt(args[0]);
			int nbToursMax = 81;
			
			File f = new File("ia/ia.pl");
			PrintWriter pw = new PrintWriter(new FileOutputStream(f,true));
			String emplacementIA = f.getAbsolutePath();
			System.out.println(emplacementIA);
			
			
			ServerSocket socket = new ServerSocket(portIA);
			Socket sockComm = socket.accept();
		    InputStream is = sockComm.getInputStream();
		    DataInputStream dis = new DataInputStream(is);
		    OutputStream os = sockComm.getOutputStream();
		    DataOutputStream dos = new DataOutputStream(os);
		    
			try {
				/* Réception du token */
				int T = CommunicationClientC.receptionToken(dis);
				
				/* Réception du signe de notre cube */
				Symbol symbol = CommunicationClientC.receptionSigne(dis);		
				
				/* Création de l'objet intéragissant avec l'IA Prolog */
				CommunicationIA commIA = new CommunicationIA(symbol, nbToursMax, emplacementIA);
				
				boolean continuer = true;
				
				if( T == 2016){
					/* Nous commençons à jouer si nous avons les croix */
					
					switch (symbol) {
						case ROND :
								/* Réception du coup adverse */
								Coup coupAdverse = CommunicationClientC.receptionCoup(dis);
								
								if (coupAdverse == null) {
									continuer = false;
									System.out.println("Signal de fin de partie reçu.\nFin de la communication");
								 } else {
									coupAdverse.type = CommunicationClientC.receptionTypCoup(dis);
									System.out.println("Coup adverse reçu : " + coupAdverse + "\n");
									
									/* On informe l'IA du coup joué par l'adversaire */
									commIA.informeCoupAdverse(coupAdverse);
									commIA.SousPlateauAJouer (coupAdverse);
									coupAdverse.type = commIA.verifieSousplateauG(coupAdverse.pos.numPlat);
									commIA.SPGInitalizerAdv (coupAdverse);
								}
								
								
						case CROIX :
							while (continuer) {
								
								/* Nous demandons le prochain coup à jouer à l'IA */
								Coup coup = commIA.coupSuivant();
								commIA.SPGInitalizerJ (coup);
								
								/* Envoi du coup à joueurQuixo */
								CommunicationClientC.envoiCoup(dos, coup);
								System.out.println("Coup joué : " + coup + "\n");
								coup.type = CommunicationClientC.receptionTypCoup(dis);
								
								if (coup.getTypeCoup() != TypeCoup.CONT) {
//									continuer = false;
									System.out.println("Coup " + coup.getTypeCoup() + " : Partie terminée.\nFin de la communication.");
								} else {
									/* Réception du coup adverse */
									coupAdverse = CommunicationClientC.receptionCoup(dis);
									
									if (coupAdverse == null) {
										continuer = false;
										System.out.println("Signal de fin de partie reçu.\nFin de la communication");
									} else {
										coupAdverse.type = CommunicationClientC.receptionTypCoup(dis);
										System.out.println("Coup adverse reçu : " + coupAdverse + "\n");
										
										/* On informe l'IA du coup joué par l'adversaire */
										commIA.informeCoupAdverse(coupAdverse);
										commIA.SousPlateauAJouer (coupAdverse);
										coupAdverse.type = commIA.verifieSousplateauG(coupAdverse.pos.numPlat);
										commIA.SPGInitalizerAdv (coupAdverse);
										
									}
								}
							}
							
							/* Partie terminée, fermeture des communications */
							dos.close();
							dis.close();
							socket.close();
							break;
						default:
							System.out.println("Moteur IA - Erreur : Signe attendu non valide.\n");
							dos.close();
							dis.close();
							socket.close();
							System.exit(2);
					}
				} else { System.out.println("Joueur Inconnue");}
				
			} catch (IOException e) {
				
				System.out.println("Client déconnecté.\nPartie terminée, fin de la communication.\n");
				dos.close();
				dis.close();
				socket.close();
			} catch (ReceptionInvalideException e) {
				System.out.println("Moteur IA - Erreur : " + e.getMessage());
				dos.close();
				dis.close();
				socket.close();
			} catch (SPException e) {
				e.printStackTrace();
				dos.close();
				dis.close();
				socket.close();
			} catch (Exception e) {
				e.printStackTrace();
				dos.close();
				dis.close();
				socket.close();
			}
		} catch (NumberFormatException e) {
			System.out.println("Moteur IA - Erreur : Entier attendu en argument (numéro de port)");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}

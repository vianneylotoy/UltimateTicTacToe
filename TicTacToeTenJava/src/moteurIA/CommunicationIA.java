package moteurIA;

import java.util.HashMap;
import java.util.Map;

import se.sics.jasper.*;

import se.sics.jasper.SICStus;
import se.sics.jasper.SPException;
import se.sics.jasper.SPQuery;
import se.sics.jasper.SPTerm;

public class CommunicationIA {

	private Maj plateau;
	private Symbol symbol;
	private Position pos;
	private IdRequest idRequest;
	private int nbrSousPlateauG;
	private Symbol symbolAdverse;
	private SICStus sp;
	private int numeroTour;
	private int nbToursMax;
	private TypSousPlateau numplat;
	private NumCaseSousPlat numsousplat;
	private GestionSousPlateauG SPG [];
	int i = 0;
	
	public CommunicationIA(Symbol symbol, int nbToursMax, String emplacementIA) throws SPException {
		this.plateau = new Maj();
		this.numplat = TypSousPlateau.E;
		nbrSousPlateauG = 0;
		this.symbol = symbol;
		if (symbol == Symbol.ROND) {
			this.symbolAdverse = Symbol.CROIX;
		} else {
			this.symbolAdverse = Symbol.ROND;
		}
		
		this.numeroTour = 0;
		this.nbToursMax = nbToursMax;
		this.sp = new SICStus();
		this.sp.load(emplacementIA);
		
		this.SPG = new GestionSousPlateauG[]{new GestionSousPlateauG(TypSousPlateau.A, TypeCoup.CONT),new GestionSousPlateauG(TypSousPlateau.B, TypeCoup.CONT),new GestionSousPlateauG(TypSousPlateau.C, TypeCoup.CONT),
											 new GestionSousPlateauG(TypSousPlateau.D, TypeCoup.CONT),new GestionSousPlateauG(TypSousPlateau.E, TypeCoup.CONT),new GestionSousPlateauG(TypSousPlateau.F, TypeCoup.CONT),
											 new GestionSousPlateauG(TypSousPlateau.G, TypeCoup.CONT),new GestionSousPlateauG(TypSousPlateau.H, TypeCoup.CONT),new GestionSousPlateauG(TypSousPlateau.I, TypeCoup.CONT)}; 
		
	}
	
	public void informeCoupAdverse(Coup coup) {
		plateau.miseAJour(coup);	
		this.numeroTour++;
	}
	
	public TypSousPlateau meilleurCoup () throws SPException{
		TypSousPlateau nump = null;
		
		String SP ="[";
		for(int i =0;i< 9;i++){
			SP += SPG[i].getStringSPTERME(symbol, symbolAdverse);
		
			if( i!=8 )
				SP +=",";
			else SP+="]";
		}
		String P = "["+SP+",[v,v,v,v,v,v,v,v,v],[v,v,v,v,v,v,v,v,v],[v,v,v,v,v,v,v,v,v],[v,v,v,v,v,v,v,v,v],[v,v,v,v,v,v,v,v,v],[v,v,v,v,v,v,v,v,v],[v,v,v,v,v,v,v,v,v],[v,v,v,v,v,v,v,v,v]]";
		Map<String, SPTerm> resultQuery = new HashMap<String, SPTerm>();
		
		String req = "lancement("+P+", a, "+symbol.getStringSPTerm()+", "+symbolAdverse.getStringSPTerm()+", "+numeroTour+", "+nbToursMax+", Case, TypeCoup, NPlateau).";
		SPQuery query = this.sp.openQuery(req, resultQuery);
		
		try {
			if (query.nextSolution()) {
				
				int Case =  (int) resultQuery.get("Case").getInteger();
				nump = TypSousPlateau.setTypSousPlateau(Case - 1);
				query.close();
			} 
			else {
				query.close();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return nump;
	}
	
	
	public void SousPlateauAJouer (Coup coup){
		switch(coup.pos.numSousPlat) {
			case UN:
				numplat = TypSousPlateau.A;
				break;
			case DEUX:
				numplat = TypSousPlateau.B;
				break;
			case TROIS:
				numplat = TypSousPlateau.C;
				break;
			case QUATRE:
				numplat = TypSousPlateau.D;
				break;
			case CINQ:
				numplat = TypSousPlateau.E;
				break;
			case SIX:
				numplat = TypSousPlateau.F;
				break;
			case SEPT:
				numplat = TypSousPlateau.G;
				break;
			case HUIT:
				numplat = TypSousPlateau.H;
				break;
			case NEUF:
				numplat = TypSousPlateau.I;
				break;
		}
	}
	public void SPGInitalizerJ (Coup coup){
		
		switch(coup.pos.numPlat){
			case A:
				i = 0;
				break;
			case B:
				i = 1;
				break;
			case C:
				i = 2;
				break;
			case D:
				i = 3;
				break;
			case E:
				i = 4;
				break;
			case F:
				i = 5;
				break;
			case G:
				i = 6;
				break;
			case H:
				i = 7;
				break;
			case I:
				i = 8;
				break;
		}
		
		if(verificateurSPFull(numplat))
			this.SPG[i] = new GestionSousPlateauG(coup.pos.numPlat, TypeCoup.NULLE);
		
		else
		this.SPG[i] = new GestionSousPlateauG(coup.pos.numPlat, coup.type);
			
		for(int j =0; j<9;j++)
		System.out.println("SPG["+j+"] numplateau ="+SPG[j].numPlateau+", SPG["+j+"] Type ="+SPG[j].type);
	}
		
	public void SPGInitalizerAdv (Coup coup){

		switch(coup.pos.numPlat){
			case A:
				i = 0;
				break;
			case B:
				i = 1;
				break;
			case C:
				i = 2;
				break;
			case D:
				i = 3;
				break;
			case E:
				i = 4;
				break;
			case F:
				i = 5;
				break;
			case G:
				i = 6;
				break;
			case H:
				i = 7;
				break;
			case I:
				i = 8;
				break;
		}
		  if(SPG[i].type == TypeCoup.CONT && coup.type != TypeCoup.GAGNANT)
			this.SPG[i] = new GestionSousPlateauG(coup.pos.numPlat, coup.type);
			
		for(int j =0; j<9;j++)
		System.out.println("SPG["+j+"] numplateau ="+SPG[j].numPlateau+", SPG["+j+"] Type ="+SPG[j].type);
	}
	
	public boolean verificateurSPFull (TypSousPlateau typSP){

		switch(typSP){
			case A:
				i = 0;
				break;
			case B:
				i = 1;
				break;
			case C:
				i = 2;
				break;
			case D:
				i = 3;
				break;
			case E:
				i = 4;
				break;
			case F:
				i = 5;
				break;
			case G:
				i = 6;
				break;
			case H:
				i = 7;
				break;
			case I:
				i = 8;
				break;
		}
		for(int j=0; j<9 ; j++){
			if(plateau.objet[i].SousPlateau[j] == Symbol.VIDE){
				return false;
			}
		}
		  return true;
	}
	
	public TypeCoup verifieSousplateauG(TypSousPlateau numplateau) throws SPException{
		TypeCoup typecoup = null;
		if(verificateurSPFull(numplateau)) 
			return typecoup = TypeCoup.NULLE;
		
		Map<String, SPTerm> resultQuery = new HashMap<String, SPTerm>();
			String req = "lancement("+plateau.getStringSPTerm()+", "+numplateau.getStringSPTerm()+", "+symbol.getStringSPTerm()+", "+symbolAdverse.getStringSPTerm()+", "+numeroTour+", "+nbToursMax+", Case, TypeCoup, NPlateau).";
			SPQuery query = this.sp.openQuery(req, resultQuery);
			
			
			if (query.nextSolution()) {
				
				char type = 'Y';
				type = resultQuery.get("TypeCoup").getString().charAt(0);
				
				switch(type) {
					case 'd':
						typecoup = TypeCoup.CONT;
						break;
					case 'g':
						typecoup = TypeCoup.GAGNANT;
						break;
					case 'n':
						typecoup = TypeCoup.NULLE;
						break;
					case 'p':
						typecoup = TypeCoup.PERDU;
						break;
					default :
						typecoup = TypeCoup.NULLE;
						break;
				}
				query.close();
				
				
			} else {
				query.close();
			}
			
		return typecoup;
	}
	
	
	public Coup coupSuivant() throws SPException {
		
		this.numeroTour++;
		
		Map<String, SPTerm> resultQuery = new HashMap<String, SPTerm>();
		
		int j = 0;
		while(j<9){
			if( SPG[j].numPlateau == numplat){
				
				if(SPG[j].type != TypeCoup.CONT){
//					for(int k =0;k<9;k++){
//						if(SPG[k].type == TypeCoup.CONT)
//							numplat = SPG[k].numPlateau;
						numplat = meilleurCoup ();
//					}
					break;
				}
			}
			j++;
		}

			String req = "lancement("+plateau.getStringSPTerm()+", "+numplat.getStringSPTerm()+", "+symbol.getStringSPTerm()+", "+symbolAdverse.getStringSPTerm()+", "+numeroTour+", "+nbToursMax+", Case, TypeCoup, NPlateau).";
			SPQuery query = this.sp.openQuery(req, resultQuery);
			
			try {
				
				if (query.nextSolution()) {
					
					int Case =  (int) resultQuery.get("Case").getInteger();
					
					numsousplat = NumCaseSousPlat.setNumCaseSousPlat(Case - 1);
					pos = new Position(numplat, numsousplat);
					
					char type = resultQuery.get("TypeCoup").getString().charAt(0);
					
					TypeCoup typeCoup = null;
					switch(type) {
						case 'd':
							typeCoup = TypeCoup.CONT;
							break;
						case 'g':
							typeCoup = TypeCoup.GAGNANT;
							nbrSousPlateauG++;
							break;
						case 'n':
							typeCoup = TypeCoup.NULLE;
							break;
						case 'p':
							typeCoup = TypeCoup.PERDU;
							break;
					}
					
					this.idRequest = IdRequest.COUP;
					
					query.close();
					
					Coup coup = new Coup(idRequest,symbol, pos ,nbrSousPlateauG);
					coup.type =typeCoup;
					informeCoupAdverse(coup);

					return coup;
				} else {
					query.close();
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		return null;
	}
}


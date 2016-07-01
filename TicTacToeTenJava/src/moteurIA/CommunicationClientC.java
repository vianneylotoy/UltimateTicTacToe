package moteurIA;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.EOFException;
import java.io.IOException;

public class CommunicationClientC {
	public static int T;
	
	public static Symbol receptionSigne(DataInput dis) throws ReceptionInvalideException, IOException, EOFException {
    	Symbol symbol;
    	int a = dis.readInt();
    	
		switch(a){
		    case 0:
		    	symbol = Symbol.ROND;
				break;
			case 1:
				symbol = Symbol.CROIX;
				break;
			default:
				throw new ReceptionInvalideException("Le signe reçu n'est ni une CROIX, ni un ROND.");
		}
		  
		return symbol;
	}
	
	public static int receptionToken(DataInput dis) throws ReceptionInvalideException, IOException, EOFException {
    	
    	T = dis.readInt();
		return T;
	}
	
	@SuppressWarnings("null")
	public static Coup receptionCoup(DataInput dis) throws ReceptionInvalideException, IOException, EOFException {
    	IdRequest id = null;
    	Symbol symbol = null;
    	TypSousPlateau numPlateau = null;
    	NumCaseSousPlat numSousPlat = null;
    	
		id = IdRequest.setIdRequest(dis.readInt());
		
		symbol = Symbol.setSymbol(dis.readInt());
		
		numPlateau = TypSousPlateau.setTypSousPlateau(dis.readInt());
		
	    numSousPlat = NumCaseSousPlat.setNumCaseSousPlat(dis.readInt());
	    
	    Position pos = new Position(numPlateau, numSousPlat);
	    
		int NbrSousPlateauG = dis.readInt();
		
		return new Coup(id, symbol, pos, NbrSousPlateauG);
	}
	
	
	public static TypeCoup receptionTypCoup(DataInput dis) throws ReceptionInvalideException, IOException, EOFException {
    	TypeCoup typCoup = null;
    	int a = dis.readInt();
    	typCoup = TypeCoup.setTypeCoup(a);
		return typCoup;
		
	}
	
	
	public static void envoiCoup(DataOutput dos, Coup coup) throws IOException {
		/*Envoie du IdRequest*/
		switch(coup.idrequete.getIdRequest()){
		
			case PARTIE:
				dos.writeInt(0);
				break;
			case COUP:
				dos.writeInt(1);
				break;
		}
		/*Envoie du SymbolJ*/
		switch (coup.getSymbol()) {
			case ROND:
				dos.writeInt(0);
				break;
			case CROIX:
				dos.writeInt(1);
				break;
			default :
				
				break;
		}
		/* Envoi du TypSousPlateau de coup joué */
		switch (coup.pos.numPlat.getTypSousPlateau()) {
			case A:
				dos.writeInt(0);
				break;
			case B:
				dos.writeInt(1);
				break;
			case C:
				dos.writeInt(2);
				break;
			case D:
				dos.writeInt(3);
				break;
			case E:
				dos.writeInt(4);
				break;
			case F:
				dos.writeInt(5);
				break;
			case G:
				dos.writeInt(6);
				break;
			case H:
				dos.writeInt(7);
				break;
			case I:
				dos.writeInt(8);
				break;
		}
		/*Envoie de la case du SousPlateau joué*/
		dos.writeInt(coup.pos.numSousPlat.getStringSPTerm() - 1);
		/*Envoie du nombre de sousplateau gagné*/
		dos.writeInt(coup.NbrSousPlateauG);
	}
	
}

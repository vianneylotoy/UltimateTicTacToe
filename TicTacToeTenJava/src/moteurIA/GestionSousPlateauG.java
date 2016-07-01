package moteurIA;

public class GestionSousPlateauG {
	TypSousPlateau numPlateau;
	TypeCoup type;
	public GestionSousPlateauG(){
		numPlateau = null;
		type = null;
	}
	public GestionSousPlateauG (TypSousPlateau numpPlateau, TypeCoup type){
		numPlateau = numpPlateau ;
		this.type = type;
	}
	public String getStringSPTERME(Symbol symbolJ, Symbol symbolAdv){
		String P = null;
		
		switch (type){
		case GAGNANT:
			P = symbolJ.getStringSPTerm();
			break;
		case PERDU:
			P = symbolAdv.getStringSPTerm();
			break;
		case CONT:
			P = Symbol.VIDE.getStringSPTerm();
			break;
		case NULLE:
			P = symbolAdv.getStringSPTerm();
		}
		return P;
	}
	
}

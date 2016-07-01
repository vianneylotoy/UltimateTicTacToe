package moteurIA;

public enum TypSousPlateau {
	A,B,C,D,E,F,G,H,I;
	public TypSousPlateau getTypSousPlateau(){
		return this;
	}
	public String getStringSPTerm() {
    	switch(this) {
    		case A:
    			return "a";
    		case B:
    			return "b";
    		case C:
    			return "c";
    		case D:
    			return "d";
    		case E:
    			return "e";
    		case F:
    			return "f";
    		case G:
    			return "g";
    		case H:
    			return "h";
    		case I:
    			return "i";
    			
    		default:
    			return " ";
    	}
    }
	public static TypSousPlateau setTypSousPlateau(int a){
		TypSousPlateau typSousPlateau = null;
		switch(a){
			case 0:
				typSousPlateau = TypSousPlateau.A;
				break;
			case 1:
				typSousPlateau = TypSousPlateau.B;
				break;
			case 2:
				typSousPlateau = TypSousPlateau.C;
				break;
			case 3:
				typSousPlateau = TypSousPlateau.D;
				break;
			case 4:
				typSousPlateau = TypSousPlateau.E;
				break;
			case 5:
				typSousPlateau = TypSousPlateau.F;
				break;
			case 6:
				typSousPlateau = TypSousPlateau.G;
				break;
			case 7:
				typSousPlateau = TypSousPlateau.H;
				break;
			case 8:
				typSousPlateau = TypSousPlateau.I;
				break;
			
			default :
				try {
					throw new ReceptionInvalideException("Le TypSousPlateau reçu est inconnu.");
				} catch (ReceptionInvalideException e) {
					e.printStackTrace();
				}
				break;
		}
		return typSousPlateau;
	}
}

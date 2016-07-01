package moteurIA;

public enum Symbol {
    ROND, CROIX, VIDE;
    
    public String getStringSPTerm() {
    	switch(this) {
    		case ROND:
    			return "o";
    		case CROIX:
    			return "x";
    		default:
    			return "v";
    	}
    }
    public static Symbol setSymbol(int a){
    	Symbol symbol = null;
		switch(a){
			case 0:
				symbol = Symbol.ROND;
				break;
			case 1:
				symbol = Symbol.CROIX;
				break;
			default :
				try {
					throw new ReceptionInvalideException("Le Symbol reçu n'est ni une ROND, ni CROIX.");
				} catch (ReceptionInvalideException e) {
					e.printStackTrace();
				}
				break;
		}
		return symbol;
	}
}

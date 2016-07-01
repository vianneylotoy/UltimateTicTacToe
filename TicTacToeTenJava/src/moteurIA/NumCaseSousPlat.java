package moteurIA;

public enum NumCaseSousPlat {
	UN,DEUX,TROIS,QUATRE,CINQ,SIX,SEPT,HUIT,NEUF;
	public int getStringSPTerm() {
    	switch(this) {
    		case UN:
    			return 1;
    		case DEUX:
    			return 2;
    		case TROIS:
    			return 3;
    		case QUATRE:
    			return 4;
    		case CINQ:
    			return 5;
    		case SIX:
    			return 6;
    		case SEPT:
    			return 7;
    		case HUIT:
    			return 8;
    		case NEUF:
    			return 9;
    			
    		default:
    			return 0;
    	
    	}
	}
	public static NumCaseSousPlat setNumCaseSousPlat(int a){
		NumCaseSousPlat numCaseSousPlat = null;
		switch(a){
			case 0:
				numCaseSousPlat = NumCaseSousPlat.UN;
				break;
			case 1:
				numCaseSousPlat = NumCaseSousPlat.DEUX;
				break;
			case 2:
				numCaseSousPlat = NumCaseSousPlat.TROIS;
				break;
			case 3:
				numCaseSousPlat = NumCaseSousPlat.QUATRE;
				break;
			case 4:
				numCaseSousPlat = NumCaseSousPlat.CINQ;
				break;
			case 5:
				numCaseSousPlat = NumCaseSousPlat.SIX;
				break;
			case 6:
				numCaseSousPlat = NumCaseSousPlat.SEPT;
				break;
			case 7:
				numCaseSousPlat = NumCaseSousPlat.HUIT;
				break;
			case 8:
				numCaseSousPlat = NumCaseSousPlat.NEUF;
				break;
			
			default :
				try {
					throw new ReceptionInvalideException("Le TypSousPlateau reçu est inconnu.");
				} catch (ReceptionInvalideException e) {
					e.printStackTrace();
				}
				break;
		}
		return numCaseSousPlat;
	}
}

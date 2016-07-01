package moteurIA;

public enum TypeCoup {
    CONT, GAGNANT, NULLE, PERDU;
    
    public static TypeCoup setTypeCoup(int a){
    	TypeCoup typcoup = null;
    		switch(a){
    			case 0:
    				typcoup = TypeCoup.CONT;
    				break;
    			case 1:
    				typcoup = TypeCoup.GAGNANT;
    				break;
    			case 2:
    				typcoup = TypeCoup.NULLE;
    				break;
    			case 3:
    				typcoup = TypeCoup.PERDU;
    				break;
    		}
    	return typcoup;
    }
}


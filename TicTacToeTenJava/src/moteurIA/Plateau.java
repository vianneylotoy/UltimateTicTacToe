package moteurIA;

import se.sics.jasper.SPTerm;

public class Plateau {
	public  Symbol[] SousPlateau;
	public  TypSousPlateau SigneSousPlateau;
	

	public Plateau (Symbol[] SousPlateau, TypSousPlateau SigneSousPlateau){
		this.SousPlateau = SousPlateau;
		this.SigneSousPlateau = SigneSousPlateau;
		
	}
	
	
	public Plateau(SPTerm SousPlateau[]) {
		this.SousPlateau = new Symbol[9];
		
		for (int i = 0; i < 9; i++) {
			switch(SousPlateau[i].toString().charAt(0)) {
			
				case 'x':
					this.SousPlateau[i] = Symbol.CROIX;
					break;
				case 'o':
					this.SousPlateau[i] = Symbol.ROND;
					break;
				case 'v':
					this.SousPlateau[i] = Symbol.VIDE;
					break;
			}
		}
	}
	
	public Symbol[] getSousPlateau() {
		return this.SousPlateau;
	}
	public TypSousPlateau getSigneSousPlateau(){
		return this.SigneSousPlateau;
	}

	
	public String getStringSPTerm (){
		String P ="[";
		for(int i =0;i< 9;i++){
			P += SousPlateau[i].getStringSPTerm();
		
			if( i!=8 )
				P +=",";
			else P+="]";
		}
		return P;
	}

}

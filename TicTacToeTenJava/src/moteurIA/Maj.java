package moteurIA;

public class Maj {
	public  Plateau[] objet;
	
	
	
	public Maj(){
		
		Symbol[] SousPlateau0 = new Symbol[9];
		Symbol[] SousPlateau1 = new Symbol[9];
		Symbol[] SousPlateau2 = new Symbol[9];
		Symbol[] SousPlateau3 = new Symbol[9];
		Symbol[] SousPlateau4 = new Symbol[9];
		Symbol[] SousPlateau5 = new Symbol[9];
		Symbol[] SousPlateau6 = new Symbol[9];
		Symbol[] SousPlateau7 = new Symbol[9];
		Symbol[] SousPlateau8 = new Symbol[9];
		
		for (int i = 0; i < 9; i++) {
			SousPlateau0[i] = Symbol.VIDE;
			SousPlateau1[i] = Symbol.VIDE;
			SousPlateau2[i] = Symbol.VIDE;
			SousPlateau3[i] = Symbol.VIDE;
			SousPlateau4[i] = Symbol.VIDE;
			SousPlateau5[i] = Symbol.VIDE;
			SousPlateau6[i] = Symbol.VIDE;
			SousPlateau7[i] = Symbol.VIDE;
			SousPlateau8[i] = Symbol.VIDE;
		}
		
		objet = new Plateau[]{new Plateau(SousPlateau0,TypSousPlateau.A),new Plateau(SousPlateau1,TypSousPlateau.B),new Plateau(SousPlateau2,TypSousPlateau.C),
							  new Plateau(SousPlateau3,TypSousPlateau.D),new Plateau(SousPlateau4,TypSousPlateau.E),new Plateau(SousPlateau5,TypSousPlateau.F),
							  new Plateau(SousPlateau6,TypSousPlateau.G),new Plateau(SousPlateau7,TypSousPlateau.H),new Plateau(SousPlateau8,TypSousPlateau.I)};
		
	}
	
	public void miseAJour(Coup coup){
		int Case = coup.pos.numSousPlat.getStringSPTerm();
		Case -=1;
		int i = 0;
		
		while(i < 9){
			
			if(objet[i].SigneSousPlateau == coup.pos.numPlat && Case>=0 && Case <=8){
				objet[i].SousPlateau[Case] = coup.getSymbol();
				break;
			}
			i++;
		}

	}
	
	public String getStringSPTerm (){
		String P = "[" ;
		for(int i =0;i< 9;i++){
				
				P += objet[i].getStringSPTerm();
		
			if( i!=8 )
				P +=",";
			else P+="]";
		}
		return P;
	}


}

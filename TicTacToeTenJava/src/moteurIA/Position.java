package moteurIA;

public class Position {
	public TypSousPlateau numPlat; /*A,B,C.....I*/
	public NumCaseSousPlat numSousPlat;/*1,2,3,.....9*/
	
	public Position(TypSousPlateau numPlat, NumCaseSousPlat numSousPlat){
		this.numPlat = numPlat;
		this.numSousPlat = numSousPlat;
	}
	public TypSousPlateau getTypSousPlateau(){
		return numPlat;
	}
	public NumCaseSousPlat getNumCaseSousPlat(){
		return numSousPlat;
	}
}

package moteurIA;

public class Coup {
	
	public Symbol symbol;
	public Position pos;
	public IdRequest idrequete;
	public int NbrSousPlateauG = 0;/*Nbr sous plateau gagné*/
	public TypeCoup type;
	
	public Coup(IdRequest idrequete, Symbol symbol, Position pos, int nbr){
		this.symbol = symbol;
		this.idrequete = idrequete;
		this.pos = pos;
		this.NbrSousPlateauG = nbr;
	}
	
	public Position getPosition(){
		return this.pos;
	}
	public TypeCoup getTypeCoup(){
		return type;
	}
	public Symbol getSymbol(){
		return this.symbol;
	}
	
	public IdRequest getIdrequest(){
		return this.idrequete;
	}
	
	public void setgetNbrSousPlateauF(int t){
		this.NbrSousPlateauG = t;
	}
	public int getNbrSousPlateauG(){
		
		return NbrSousPlateauG;
	}
	
	public String toString(){
		return "["+pos.numPlat+","+pos.numSousPlat+"]("+symbol+")->["+idrequete+"]";
	}
	
	public boolean equals(Object obj){
		if(this == obj)
			return true;
		if(obj == null)
			return false;
		if(!(obj instanceof Coup))
			return false;
		Coup other = (Coup) obj;
		if (pos.numSousPlat != other.pos.numSousPlat) {
			return false;
		}
		if (symbol != null && other.symbol != null && symbol != other.symbol) {
			return false;
		}
		if (pos.numPlat != null && other.pos.numPlat != null && pos.numPlat  != other.pos.numPlat ) {
			return false;
		}
		if (idrequete != other.idrequete) {
			return false;
		}
		return true;
	}
}

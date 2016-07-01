package moteurIA;

public enum IdRequest {
	PARTIE,COUP;
	
	public IdRequest getIdRequest(){
		return this;
	}
	public static IdRequest setIdRequest(int a){
		IdRequest idrequest = null;
		switch(a){
			case 0:
				idrequest = IdRequest.PARTIE;
				break;
			case 1:
				idrequest = IdRequest.COUP;
				break;
			default :
				try {
					throw new ReceptionInvalideException("Le IdRequest reçu n'est ni une Partie, ni Coup.");
				} catch (ReceptionInvalideException e) {
					e.printStackTrace();
				}
				break;
		}
		return idrequest;
	}
}

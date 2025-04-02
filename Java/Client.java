package Java;

class Client {
        
    public static void main(String[] args) {
        //inizializzo i livelli dell'host mittente
        
        DataLink ddlSend=new DataLink();
        Network netwSend=new Network();
        Trasporto transpSend=new Trasporto();
        Applicativo applSend=new Applicativo(1, transpSend);

        //inizializzo i livelli dell'host ricevente
        DataLink ddlReceiv=new DataLink();
        Network netwReceiv=new Network();
        Trasporto transpReceiv=new Trasporto();
        Applicativo applReceiv=new Applicativo(2, transpReceiv);
        

        //mando messaggio tramite applicativo
        String myletter = "Caro amico ti scrivo...";
        applSend.sendMessage(myletter);

    }
    
}
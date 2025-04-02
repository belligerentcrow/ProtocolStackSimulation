package Java;

public class Applicativo implements Protocollo {
    int pID;
    Trasporto livT;

    public Applicativo(int p, Trasporto t){
        this.pID =p;
        this.livT = t;
    }

    public void sendMessage(String p){
        //create PDU calling incapsulate with the given string
    }

    public PDU incapsulate(PDU p){
        //incapsulate string to message and send below
        return null;
    }
    public PDU decapsulate(PDU p){
        //decapsulate message to string and call printstring
        return null;
    }
    public String printString(){
        return null;
    }
}

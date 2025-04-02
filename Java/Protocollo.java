package Java;

public interface Protocollo {
    
    public PDU incapsulate(PDU p);
    public PDU decapsulate(PDU p);
}

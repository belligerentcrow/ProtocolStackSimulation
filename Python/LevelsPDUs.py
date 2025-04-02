from Python.PDU import PDU;

class Messaggio(PDU):
        payload;
        header;

class Segmento(PDU):
        payload;
        header;

class Datagramma(PDU):
        payload;
        header;

class Frame(PDU):
        payload;
        header;
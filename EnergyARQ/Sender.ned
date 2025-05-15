simple Sender
{
    parameters:
        int    limit        = default(100);          // packets to send
        double timeout      @unit(s)  = default(1s); // ← add unit tag
        double txPower_mW   @unit(mW) = default(100mW);
        int    pktLenBytes  = default(1000);
        @display("i=device/antenna");
    gates:
        output out;
        input  in;
}



package energyarq;

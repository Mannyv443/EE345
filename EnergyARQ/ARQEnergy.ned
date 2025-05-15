package energyarq;
channel Link extends ned.DatarateChannel
{
    delay    = 1ms;     // propagation delay
    datarate = 1Mbps;   // link speed
    ber      = default(1e-5);   // bit-error rate (configurable)
}

network ARQEnergy
{
    submodules:
        sender:      Sender;
        destination: Destination;
    connections:
        sender.out      --> Link --> destination.in;
        destination.out --> Link --> sender.in;
}

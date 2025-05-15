namespace energyarq;

packet DataPkt {
    int seqNum;
    int payloadLengthBytes = 1000;
}

packet AckPkt {
    int seqNum;
}

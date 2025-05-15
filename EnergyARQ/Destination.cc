#include <omnetpp.h>
#include "EnergyPkt_m.h"

using namespace omnetpp;

class Destination : public cSimpleModule
{
  protected:
    void handleMessage(cMessage *msg) override {
        auto *data = check_and_cast<energyarq::DataPkt *>(msg);
        if (!data->hasBitError()) {
            auto *ack = new energyarq::AckPkt("ack");
            ack->setSeqNum(data->getSeqNum());
            send(ack, "out");
        }
        delete data;
    }
};

Define_Module(Destination);

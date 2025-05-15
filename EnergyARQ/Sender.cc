#include <omnetpp.h>
#include "EnergyPkt_m.h"

using namespace omnetpp;

class Sender : public cSimpleModule
{
  private:
    int      seqNum      = 0;
    int      limit;
    double   timeout;
    double   txPowerW;
    int      pktLenBytes;
    cMessage *timeoutEvt = nullptr;
    cStdDev  energyStat;

    void sendData() {
        auto *pkt = new energyarq::DataPkt("data");

        pkt->setSeqNum(seqNum);
        pkt->setByteLength(pktLenBytes);

        // energy = power × airtime
        double datarate = gate("out")->getChannel()->par("datarate").doubleValue();
        double txTime   = pkt->getBitLength() / datarate;
        energyStat.collect(txPowerW * txTime);

        send(pkt, "out");
        scheduleAt(simTime() + timeout, timeoutEvt);
    }

  protected:
    void initialize() override {
        limit       = par("limit");
        timeout     = par("timeout");
        txPowerW    = par("txPower_mW").doubleValue() / 1e3;   // mW → W
        pktLenBytes = par("pktLenBytes");
        timeoutEvt  = new cMessage("timeout");
        WATCH(seqNum);
        sendData();
    }

    void handleMessage(cMessage *msg) override {
        if (msg == timeoutEvt) {
            // retransmit same seqNum
            sendData();
        } else {
            // ACK arrived
            cancelEvent(timeoutEvt);
            delete msg;
            if (++seqNum < limit)
                sendData();
        }
    }

    void finish() override {
        recordStatistic(&energyStat);   // writes mean, stddev
    }
};

Define_Module(Sender);

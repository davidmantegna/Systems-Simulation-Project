/*
 * AbstractFifo.h
 *
 *  Created on: Apr 20, 2018
 *      Author: davide
 */

#ifndef ABSTRACTFIFO_H_
#define ABSTRACTFIFO_H_

#include <omnetpp.h>

using namespace omnetpp;

namespace queueing {

class AbstractFifo : public cSimpleModule
{
  protected:
    cMessage *msgServiced;
    cMessage *endServiceMsg;
    cQueue queue;
    simsignal_t qlenSignal;
    simsignal_t busySignal;
    simsignal_t queueingTimeSignal;

  public:
    AbstractFifo();
    virtual ~AbstractFifo();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    // hook functions to (re)define behaviour
    virtual void arrival(cMessage *msg) {}
    virtual simtime_t startService(cMessage *msg) = 0;
    virtual void endService(cMessage *msg) = 0;
};

}; /* namespace queueing */

#endif /* ABSTRACTFIFO_H_ */

/*
 * AbstractFifo.cc
 *
 *  Created on: Apr 20, 2018
 *      Author: davide
 */

#include "AbstractFifo.h"

namespace queueing {

AbstractFifo::AbstractFifo()
{
    msgServiced = endServiceMsg = nullptr;
}

AbstractFifo::~AbstractFifo()
{
    delete msgServiced;
    cancelAndDelete(endServiceMsg);
}

void AbstractFifo::initialize()
{
    endServiceMsg = new cMessage("end-service");
    queue.setName("queue");

    qlenSignal = registerSignal("qlen");
    busySignal = registerSignal("busy");
    queueingTimeSignal = registerSignal("queueingTime");
    emit(qlenSignal, queue.getLength());
    emit(busySignal, false);
}

void AbstractFifo::handleMessage(cMessage *msg)
{
    if (msg == endServiceMsg) {
        endService(msgServiced);
        if (queue.isEmpty()) {
            msgServiced = nullptr;
            emit(busySignal, false);
        }
        else {
            msgServiced = (cMessage *)queue.pop();
            emit(qlenSignal, queue.getLength());
            emit(queueingTimeSignal, simTime() - msgServiced->getTimestamp());
            simtime_t serviceTime = startService(msgServiced);
            scheduleAt(simTime()+serviceTime, endServiceMsg);
        }
    }
    else if (!msgServiced) {
        arrival(msg);
        msgServiced = msg;
        emit(queueingTimeSignal, SIMTIME_ZERO);
        simtime_t serviceTime = startService(msgServiced);
        scheduleAt(simTime()+serviceTime, endServiceMsg);
        emit(busySignal, true);
    }
    else {
        arrival(msg);
        queue.insert(msg);
        msg->setTimestamp();
        emit(qlenSignal, queue.getLength());
    }
}

} /* namespace queueing */

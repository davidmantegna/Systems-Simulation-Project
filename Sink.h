#ifndef __QUEUEING_SINK_H
#define __QUEUEING_SINK_H

#include "QueueingDefs.h"

namespace queueing {

/**
 * Consumes jobs; see NED file for more info.
 */
class QUEUEING_API Sink : public cSimpleModule
{
  private:
    simsignal_t arrivalSignal;
    simsignal_t fromBoxArrivalSignal;
//    simsignal_t totalQueueingTimeSignal;
//    simsignal_t queuesVisitedSignal;
//    simsignal_t totalServiceTimeSignal;
//    simsignal_t totalDelayTimeSignal;
//    simsignal_t delaysVisitedSignal;
//    simsignal_t generationSignal;
    bool keepJobs;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

}; //namespace

#endif


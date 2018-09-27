#ifndef __QUEUEING_DELAY_H
#define __QUEUEING_DELAY_H

#include "QueueingDefs.h"

namespace queueing {

/**
 * Delays the incoming messages
 */
class QUEUEING_API Delay : public cSimpleModule
{
    private:
		simsignal_t delayedJobsSignal;
		simsignal_t retrialPhaseTimeSignal;
        int currentlyStored;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void refreshDisplay() const override;
};

}; //namespace

#endif


#ifndef __QUEUEING_SERVER_H
#define __QUEUEING_SERVER_H

#include "IServer.h"

namespace queueing {

class Job;
class SelectionStrategy;

class QUEUEING_API Server : public cSimpleModule, public IServer
{
    private:
        simsignal_t busySignal;
        simsignal_t queueVacationSignal;
        simsignal_t queueBusySignal;
        simsignal_t vacationSignal;
        bool allocated;
        simtime_t vacationTime;

        SelectionStrategy *selectionStrategy;

        Job *jobServiced;
        cMessage *endServiceMsg;
        cMessage *endVacationMsg;
        bool vacation;

    protected:
        virtual void initialize() override;
        virtual int numInitStages() const override {return 2;}
        virtual void handleMessage(cMessage *msg) override;
        virtual void refreshDisplay() const override;
        virtual void finish() override;

    public:
        Server();
        virtual ~Server();
        virtual bool isIdle() override;
        virtual void allocate() override;
        bool inVacation();
        int lengthQueue();
};

};

#endif



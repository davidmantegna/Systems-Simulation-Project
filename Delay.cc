#include "Delay.h"
#include "Job.h"

namespace queueing {

Define_Module(Delay);

void Delay::initialize()
{
    currentlyStored = 0;
    delayedJobsSignal = registerSignal("delayedJobs");

    retrialPhaseTimeSignal = registerSignal("lengthRetrial");

    emit(delayedJobsSignal, 0);
    WATCH(currentlyStored);
}

void Delay::handleMessage(cMessage *msg)
{
    Job *job = check_and_cast<Job *>(msg);

    if (!job->isSelfMessage()) {
        // if it is not a self-message, send it to ourselves with a delay
        currentlyStored++;
        double delay = par("delay");
        scheduleAt(simTime() + delay, job);
    }
    else {
        job->fromBox = true;
        job->setDelayCount(job->getDelayCount()+1);
        simtime_t d = simTime() - job->getSendingTime();
        job->setTotalDelayTime(job->getTotalDelayTime() + d);
        //EV<< "Delay Time RetrialBox: " << job->getTotalDelayTime() << "\n\n\n\n";
        emit(retrialPhaseTimeSignal, job->getTotalDelayTime());

        // if it was a self message (ie. we have already delayed) so we send it out
        currentlyStored--;
        send(job, "out");
    }

    emit(delayedJobsSignal, currentlyStored);

}

void Delay::refreshDisplay() const
{
    getDisplayString().setTagArg("i", 1, currentlyStored == 0 ? "" : "cyan");
}


}; //namespace


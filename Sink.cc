#include "Sink.h"
#include "Job.h"

namespace queueing {

Define_Module(Sink);

void Sink::initialize()
{
    arrivalSignal = registerSignal("generalArrival");
    fromBoxArrivalSignal = registerSignal("fromBoxArrival");
//    totalQueueingTimeSignal = registerSignal("totalQueueingTime");
//    queuesVisitedSignal = registerSignal("queuesVisited");
//    totalServiceTimeSignal = registerSignal("totalServiceTime");
//    totalDelayTimeSignal = registerSignal("totalDelayTime");
//    delaysVisitedSignal = registerSignal("delaysVisited");
//    generationSignal = registerSignal("generation");
    keepJobs = par("keepJobs");
}

void Sink::handleMessage(cMessage *msg)
{
    Job *job = check_and_cast<Job *>(msg);
    if(job->fromBox){
        EV<< "From Box lifeTime: " << simTime()- job->getCreationTime() << "\n\n\n";
        emit(fromBoxArrivalSignal, simTime()- job->getCreationTime());
    }

    EV<< "General lifeTime: " << simTime()- job->getCreationTime() << "\n\n\n";
    emit(arrivalSignal, simTime()- job->getCreationTime());
//    emit(totalQueueingTimeSignal, job->getTotalQueueingTime());
//    emit(queuesVisitedSignal, job->getQueueCount());
//    emit(totalServiceTimeSignal, job->getTotalServiceTime());
//    emit(totalDelayTimeSignal, job->getTotalDelayTime());
//    emit(delaysVisitedSignal, job->getDelayCount());
//    emit(generationSignal, job->getGeneration());
    if (!keepJobs)
        delete msg;
}

void Sink::finish()
{
    // TODO missing scalar statistics
}

}; //namespace


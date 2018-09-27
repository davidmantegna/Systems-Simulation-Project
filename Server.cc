#include "Server.h"
#include "Job.h"
#include "SelectionStrategies.h"
#include "IPassiveQueue.h"

namespace queueing {

Define_Module(Server);

Server::Server()
{
    selectionStrategy = nullptr;
    jobServiced = nullptr;
    endServiceMsg = nullptr;
    allocated = false;
}

Server::~Server()
{
    delete selectionStrategy;
    delete jobServiced;
    cancelAndDelete(endServiceMsg);
}

void Server::initialize()
{
    queueVacationSignal = registerSignal("lengthVacation");
    queueBusySignal = registerSignal("lengthBusy");
    busySignal = registerSignal("busy");
    vacationSignal = registerSignal("vacation");
    emit(busySignal, false);

    emit(queueVacationSignal, 0);
    emit(queueBusySignal, 0);

    vacationTime = par("vacationTime");
    endVacationMsg = new cMessage("end-vacation");
    endServiceMsg = new cMessage("end-service");

    vacation = false;
    jobServiced = nullptr;
    allocated = false;

    selectionStrategy = SelectionStrategy::create("priority", this, true);
    if (!selectionStrategy)
        throw cRuntimeError("invalid selection strategy");
}

void Server::handleMessage(cMessage *msg)
{
    int gateOutput;
    cGate *out;
    double p = 0;

    if (msg == endServiceMsg) {

        emit(queueBusySignal, lengthQueue());
        vacation = false;
        cancelEvent(endVacationMsg);
        ASSERT(jobServiced != nullptr);
        ASSERT(allocated);

        simtime_t d = simTime() - endServiceMsg->getSendingTime();
        jobServiced->setTotalServiceTime(jobServiced->getTotalServiceTime() + d);

        if(jobServiced->firstPhase){

            jobServiced->firstPhase = false;
            jobServiced->secondPhase = true;

            p = uniform(0, 1);
            if (p < 0.7){
                out = gate("out", 0); // send to RetrialBox
            }else{
                out = gate("out", 1); // send to Queue
            }
        }else if(jobServiced->secondPhase){
            out = gate("out", 2); // send to Sink
            jobServiced->secondPhase = false;
        }

        send(jobServiced, out);
        jobServiced = nullptr;
        allocated = false;
        emit(busySignal, false);

        // examine all input queues, and request a new job from a non empty queue
        int k = selectionStrategy->select();

        if (k >= 0)
        {
            cGate *gate = selectionStrategy->selectableGate(k);
            check_and_cast<IPassiveQueue *>(gate->getOwnerModule())->request(gate->getIndex());
        }
        else
        {
            emit(busySignal, false);
            emit(vacationSignal, 1);

            emit(queueVacationSignal, lengthQueue());
            vacation = true;
            scheduleAt(simTime() + vacationTime, endVacationMsg);
        }

    }else if (msg == endVacationMsg){

        emit(queueVacationSignal, lengthQueue());
        int k = selectionStrategy->select();
        if (k >= 0)
        {
            vacation = false;
            cancelEvent(endVacationMsg);
            cGate *gate = selectionStrategy->selectableGate(k);
            check_and_cast<IPassiveQueue *>(gate->getOwnerModule())->request(gate->getIndex());
        }
        else
        {
            vacation = true;
            scheduleAt(simTime() + vacationTime, endVacationMsg);
        }

    }else{

        if (!allocated)
            error("job arrived, but the sender did not call allocate() previously");
        if (jobServiced)
            throw cRuntimeError("a new job arrived while already servicing one");

        jobServiced = check_and_cast<Job *>(msg);
        simtime_t serviceTime;

        if(jobServiced->firstPhase){
            serviceTime = erlang_k(3, 1);

        }else if(jobServiced->secondPhase){

            if(jobServiced->fromQueue){
                serviceTime = erlang_k(2, 0.5);

            }else if(jobServiced->fromBox){
                serviceTime = erlang_k(2, 0.33);

            }

        }

        scheduleAt(simTime() + serviceTime, endServiceMsg);
        emit(queueBusySignal, lengthQueue());
        emit(busySignal, true);

    }
}

bool Server::inVacation()
{
  return vacation;
}


void Server::refreshDisplay() const
{
    getDisplayString().setTagArg("i2", 0, jobServiced ? "status/execute" : "");
    getDisplayString().setTagArg("i", 1, vacation ? "yellow" : "");
}

void Server::finish()
{
}

bool Server::isIdle()
{
    return !allocated;
}

void Server::allocate()
{
    allocated = true;
}

int Server::lengthQueue()
{
  cGate *gate = selectionStrategy->selectableGate(0);
  int l = check_and_cast<IPassiveQueue *>(gate->getOwnerModule())->length();
  return l;
}

}; //namespace


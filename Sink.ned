simple Sink
{
    parameters:
        @group(Queueing);
        @display("i=block/sink");
        @signal[generalArrival](type="simtime_t");
        @signal[fromBoxArrival](type="simtime_t");
//        @signal[totalQueueingTime](type="simtime_t");
//        @signal[totalDelayTime](type="simtime_t");
//        @signal[totalServiceTime](type="simtime_t");
//        @signal[queuesVisited](type="long");
//        @signal[delaysVisited](type="long");
//        @signal[generation](type="long");
        @statistic[generalLifeTime](title="lifetime of arrived jobs"; source="generalArrival"; unit=s; record=vector,stats; interpolationmode=none);
        @statistic[fromBoxLifeTime](title="lifetime of jobs arrived from RetrialBox"; source="fromBoxArrival"; unit=s; record=vector,stats; interpolationmode=none);
//        @statistic[totalQueueingTime](title="the total time spent in queues by arrived jobs";unit=s;record=vector?,mean,max;interpolationmode=none);
//        @statistic[totalDelayTime](title="the total time spent in delay nodes by arrived jobs";unit=s;record=vector?,mean,max;interpolationmode=none);
//        @statistic[totalServiceTime](title="the total time spent  by arrived jobs";unit=s;record=vector?,mean,max;interpolationmode=none);
//        @statistic[queuesVisited](title="the total number of queues visited by arrived jobs";record=vector?,mean,max;interpolationmode=none);
//        @statistic[delaysVisited](title="the total number of delays visited by arrived jobs";record=vector?,mean,max;interpolationmode=none);
//        @statistic[generation](title="the generation of the arrived jobs";record=vector?,mean,max;interpolationmode=none);
        bool keepJobs = default(false); // whether to keep the received jobs till the end of simulation
    gates:
        input in;
}


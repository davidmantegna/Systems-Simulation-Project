network TwoPhaseNet
{
    @display("bgb=519,270");
    submodules:

        Source: Source {
            parameters:
                @display("p=115,106");
        }

        Queue: PassiveQueue {
            parameters:
                @display("p=206,106");
        }

        Server: Server {
            @display("p=337,106");
        }

        RetrialBox: Delay {
            @display("p=260,180");
        }

        Sink: Sink {
            parameters:
                @display("p=423,106");
        }

    connections:

        Source.out --> Queue.in++;
        Queue.out++ --> Server.in++;
        Server.out++ --> RetrialBox.in++;
        RetrialBox.out --> Queue.in++;
		Server.out++ --> Queue.in++;
        Server.out++ --> Sink.in;
}

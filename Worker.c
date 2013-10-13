//  PI Worker
//  Connects PULL socket to tcp://localhost:5557
//  Connects PUSH socket to tcp://localhost:5558
//  Sends results to Evaluater via that socket

#include "Helper.h"

int main (void)
{
    //  Socket to receive messages on
    void *context = zmq_ctx_new ();
    void *receiver = zmq_socket (context, ZMQ_PULL);
    zmq_connect (receiver, "tcp://localhost:5557");

    //  Socket to send messages to Evaluater
    void *sender = zmq_socket (context, ZMQ_PUSH);
    zmq_connect (sender, "tcp://localhost:5558");

    //  Process tasks forever
    while (1) {
        char *xstring = s_recv (receiver);
        char *ystring = s_recv (receiver);

        float xCoordinate;
        float yCoordinate;
        int hit;

        fflush (stdout);
        xCoordinate = atof (xstring);    // convert string back to float
        yCoordinate = atof (ystring);    // convert string back to float
        free (xstring);
        free (ystring); 

        printf("Coordinate: %f ", 2 * (xCoordinate * yCoordinate));

        hit = ((yCoordinate * yCoordinate) + (xCoordinate * xCoordinate)) < 1;

        printf("Hit: %d \n", hit);

        char result [10];
        sprintf (result, "%d", hit);
        s_send (sender, result);        //  Send results to Evaluater
    }
    zmq_close (receiver);
    zmq_close (sender);
    zmq_ctx_destroy (context);
    return 0;
}
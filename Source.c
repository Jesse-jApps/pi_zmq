//  Source
//  Generating Random numbers
//  Binds PUSH socket to tcp://localhost:5557
//  Sends 2 random numbers to workers via that socket

#include "Helper.h"

int main (void)
{
    int task_nbr;
    int tasks;

    void *context = zmq_ctx_new ();

    //  Socket to send messages on
    void *sender = zmq_socket (context, ZMQ_PUSH);
    zmq_bind (sender, "tcp://*:5557");

    printf ("How many Tasks do you want to send: ");
    scanf ("%d", &tasks);

    //Initialising Seed
    srand(1);

    for (task_nbr = 0; task_nbr < tasks; task_nbr++) {
        float xCoordinate;
        float yCoordinate;

        xCoordinate = (rand() % 100 + 1) / 100.0;
        yCoordinate = (rand() % 100 + 1) / 100.0;

        char xstring [10];
        char ystring [10];

        sprintf (xstring, "%f", xCoordinate);
        sprintf (ystring, "%f", yCoordinate);

        s_sendmore (sender, xstring);
        s_send (sender, ystring);
    }
    printf ("No More numbers! \n");

    zmq_close (sender);
    zmq_ctx_destroy (context);
    return 0;
}
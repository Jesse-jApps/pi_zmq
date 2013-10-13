//  Evaluater
//  Binds PULL socket to tcp://localhost:5558
//  Collects results from Workers via that socket

#include "Helper.h"

int main (void)
{
    //  Prepare our context and socket
    void *context = zmq_ctx_new ();
    void *receiver = zmq_socket (context, ZMQ_PULL);
    zmq_bind (receiver, "tcp://*:5558");

    int all = 0;
    int hits = 0;
    double pi;

    while(1) {
       char *string = s_recv (receiver);
       int hit = atoi (string);
       free (string);
       hits = hits + hit;
       all++;

       pi = 4*(double)hits/all;


       printf("Overall: %d hits: %d and Pi: %f \n", all, hits, pi);

       fflush (stdout);
    }

    zmq_close (receiver);
    zmq_ctx_destroy (context);
    return 0;
}
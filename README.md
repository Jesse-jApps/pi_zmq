pi_zmq
======

PI Calculation via Monte-Carlo-Algorithmus on top of ZeroMQ

This little Programm calculates the Number PI using the Monte-Carlo-Algorithmus.
Build on top of ZMQ the process can be scaled on many as desired clients.

Idea:
- Source: The Source supplies a chain of indefinit random numbers and loops through it.
- Worker: The Worker receives 2 random numbers from the Source and calcualtes if it hits the circle.
- Evaluater: The Worker is sending the result to the Evaluater, who calcualtes the number Pi, based on how many hits compared to total shoots there has been.

Scalable:
The calculation if the shoot was a hit, made by the worker can be scaled to any desired amount of clients.

Test Results:

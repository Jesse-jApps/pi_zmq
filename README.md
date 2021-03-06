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

Installation & Usage:

1. ZMQ needs to be installed and working

2. Compile sources with

- "clang -Wall Source.c -o Source -L/usr/local/lib -lzmq"
- "clang -Wall Worker.c -o Worker -L/usr/local/lib -lzmq"
- "clang -Wall Evaluater.c -o Evaluater -L/usr/local/lib -lzmq"

3. Besure to run Worker and Evaluater before you start the Source, otherwise you might not get any results



TODO's:

1: Benchmarking feature

- implement Collector between Worker and Evaluater
- Collector gets all Results from Worker (just like the Evaluater right now)
- Evaluater asks Collector for partial results in defined time intervall and is then able to calculate calculation time

2: Scaling the Source:

- Source and Worker will be one program. Every Worker can become a new Source, when it realizes that it is not becoming enough tasks
- Source will initialize own workers and is able to kill them, when they are no longer needed
- If a Worker becomes a Source it asks the parent Source for an Intervall of random numbers (Parentsource has to plant new seed)
- Workers have to observe socket latency as well as cpu usage

﻿# Distributed-Computation-based-Matrix-Solver


To use the Distributed Computation-based Matrix Solver, follow these steps:

1.Debug the client1 file.
        gcc client1.c -o client1  (in cmd)
2.Debug the multiclient server file.
        gcc multiclient.c -o multiclient  (in cmd)
3.Debug the client0 file (helper server creator).
        gcc client0.c -o client0  (in cmd)
4.Run the server file.
        ./multiserver
5.Run the client1 file in two different terminals to create helper servers.
        ./client1
6.Run client0 to take user input matrix file.
        ./client0
7.Give Input 3x3 matrix to client0
And output will be printed
By following these steps, you can effectively utilize the Distributed Computation-based Matrix Solver to solve 3x3 matrices.

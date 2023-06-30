#Distributed Computation-based Matrix Solver

The Distributed Computation-based Matrix Solver offers a powerful solution for solving 3x3 matrices efficiently. By following the steps below, you can effectively utilize this solver:

Debug the client1 file:

Open the terminal and execute the following command:
Copy code
gcc client1.c -o client1
Debug the multiclient server file:

In the terminal, run the following command:
Copy code
gcc multiclient.c -o multiclient
Debug the client0 file (helper server creator):

Compile the client0 file by running the command in the terminal:
Copy code
gcc client0.c -o client0
Run the server file:

Execute the multiclient server program by running the following command:
bash
Copy code
./multiserver
Run the client1 file in two different terminals to create helper servers:

Open two separate terminal windows and execute the following command in each:
bash
Copy code
./client1
Run client0 to take user input matrix file:

In another terminal, run the command:
bash
Copy code
./client0
Provide a 3x3 matrix as input to client0 and observe the output.

By following these steps, you can utilize the Distributed Computation-based Matrix Solver effectively and obtain accurate solutions for 3x3 matrices.

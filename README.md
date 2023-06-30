# Distributed Computation-based Matrix Solver

The Distributed Computation-based Matrix Solver offers a powerful solution for solving 3x3 matrices efficiently. By following the steps below, you can effectively utilize this solver.

## Getting Started

### Prerequisites
- GCC (GNU Compiler Collection)

### Installation and Usage

1. Debug the client1 file:
   - Open the terminal and execute the following command:
     ```
     gcc client1.c -o client1
     ```

2. Debug the multiclient server file:
   - In the terminal, run the following command:
     ```
     gcc multiclient.c -o multiclient
     ```

3. Debug the client0 file (helper server creator):
   - Compile the client0 file by running the command in the terminal:
     ```
     gcc client0.c -o client0
     ```

4. Run the server file:
   - Execute the multiclient server program by running the following command:
     ```
     ./multiserver
     ```

5. Run the client1 file in two different terminals to create helper servers:
   - Open two separate terminal windows and execute the following command in each:
     ```
     ./client1
     ```

6. Run client0 to take user input matrix file:
   - In another terminal, run the command:
     ```
     ./client0
     ```

7. Provide a 3x3 matrix as input to client0 and observe the output.


## Acknowledgements

- [GNU Compiler Collection](https://gcc.gnu.org/) - The GCC (GNU Compiler Collection) used for compiling the code.

---

By following these steps, you can utilize the Distributed Computation-based Matrix Solver effectively and obtain accurate solutions for 3x3 matrices.

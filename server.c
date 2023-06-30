#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "0.0.0.0"
#define SERVER_PORT 5000

int main() {
    // create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // create server address structure
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_address.sin_port = htons(SERVER_PORT);

    // bind socket to address and port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // listen for client connections
    if (listen(server_socket, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // accept client0 connection and receive matrix
    int client0_socket = accept(server_socket, NULL, NULL);
    if (client0_socket < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    printf("Client0 connected\n");

    // receive matrix from client0
    int matrix[3][3];
    if (recv(client0_socket, matrix, sizeof(matrix), 0) < 0) {
        perror("receive failed");
        exit(EXIT_FAILURE);
    }
    printf("Received matrix from client0:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // divide matrix into 3 submatrices
    int submatrices[3][3][3];
    int row_start = 0;
    int row_end = 2;
    for (int i = 0; i < 3; i++) {
        int col_start = 0;
        int col_end = 2;
        for (int j = 0; j < 3; j++) {
            for (int k = row_start; k <= row_end; k++) {
                for (int l = col_start; l <= col_end; l++) {
                    submatrices[i][k - row_start][l - col_start] = matrix[k][l];
                }
            }
            col_start += 3;
            col_end += 3;
        }
        row_start += 3;
        row_end += 3;
    }

    // accept client1 connection and send submatrix 1
    int client1_socket = accept(server_socket, NULL, NULL);
    if (client1_socket < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    printf("Client1 connected\n");

    if (send(client1_socket, submatrices[0], sizeof(submatrices[0]), 0) < 0) {
        perror("send failed");
        exit(EXIT_FAILURE);
    }
    printf("Sent submatrix 1 to client1\n");

    // accept client2 connection and send submatrix 2
    int client2_socket = accept(server_socket, NULL, NULL);
    if (client2_socket < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    printf("Client2 connected\n");

    if (send(client2_socket, submatrices[1], sizeof(submatrices[1]), 0) < 0) {
        perror("send failed");
        exit(EXIT_FAILURE);
    }
    printf("Sent submatrix 2 to client2\n");

    // accept client3 connection and send submatrix 3
    int client3_socket = accept(server_socket, NULL, NULL);
    if (client3_socket < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    printf("Client3 connected\n");

    if (send(client3_socket, submatrices[2], sizeof(submatrices[2]), 0) < 0) {
        perror("send failed");
        exit(EXIT_FAILURE);
    }
    printf("Sent submatrix 3 to client3\n");

    // close sockets
    close(client0_socket);
    close(client1_socket);
    close(client2_socket);
    close(client3_socket);
    close(server_socket);

    return 0;
}


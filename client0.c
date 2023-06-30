#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
#define PORT 8080


int main() {

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    



    // create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // set server address and port
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("invalid address");
        exit(EXIT_FAILURE);
    }

    // connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }
    
    
        // Prompt the user to input the matrix
    int matrix[3][3];
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Send the matrix to the server
    if (send(sock, matrix, sizeof(matrix), 0) < 0) {
        perror("Failed to send matrix to server");
        exit(1);
    }

    printf("Matrix sent to server successfully!\n");




    // read matrix from user
//    int matrix[3][3];
//    printf("Enter a 3x3 matrix:\n");
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
//            scanf("%d", &matrix[i][j]);
//        }
//    }

    // send matrix to server
//    char matrix_str[50];
//    sprintf(matrix_str, "%d,%d,%d,%d,%d,%d,%d,%d,%d",
//            matrix[0][0], matrix[0][1], matrix[0][2],
//            matrix[1][0], matrix[1][1], matrix[1][2],
//            matrix[2][0], matrix[2][1], matrix[2][2]);
//    if (send(sock, matrix_str, strlen(matrix_str), 0) == -1) {
//        perror("send failed");
//        exit(EXIT_FAILURE);
//    }
    
int final_determinant;
// receive final determinant from server
if (recv(sock, &final_determinant, sizeof(final_determinant), 0) < 0) {
    perror("receive failed");
    exit(EXIT_FAILURE);
}
printf("Received final determinant from server: %d\n", final_determinant);


    // close the socket and exit
    close(sock);
    return 0;
}


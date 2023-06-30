#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    int submatrix[2][2];

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

    // receive submatrix from server
    if (recv(sock, submatrix, sizeof(submatrix), 0) < 0) {
        perror("receive failed");
        exit(EXIT_FAILURE);
    }
    printf("Received submatrix from server\n");

    // calculate determinant of submatrix
    int determinant = (submatrix[0][0]*submatrix[1][1]) - (submatrix[0][1]*submatrix[1][0]);
    printf("Calculated determinant of submatrix: %d\n", determinant);

    // send determinant to server
    if (send(sock, &determinant, sizeof(determinant), 0) < 0) {
        perror("send failed");
        exit(EXIT_FAILURE);
    }
    printf("Sent determinant of submatrix to server\n");

    // close socket
    close(sock);

    return 0;
}


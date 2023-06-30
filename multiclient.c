#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
    int server_socket, client_socket[4], new_socket;
    struct sockaddr_in server_addr, client_addr;
    int opt = 1;
    int addrlen = sizeof(server_addr);
    int client_count = 0;

    // create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // set socket options
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // set server address parameters
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // bind socket to address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // listen for connections
    if (listen(server_socket, 4) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started\n");
    

    // accept connections from clients
    while (client_count < 4) {
        if ((new_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&addrlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }
        printf("Accepted connection from client %d\n", client_count);

        // store client socket
        client_socket[client_count++] = new_socket;
    }



     int matrix[3][3];
     if (recv(client_socket[0], &matrix, sizeof(matrix), 0) < 0) {
            perror("Failed to receive matrix from client");
            close(client_socket[0]);
        }

    
        printf("Matrix received from client:\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
        
        
        


// send adjacent matrices to clients
int submatrix[2][2];
for (int i = 1; i <= 3; i++) {
    // Calculate submatrix based on i value
    if (i == 1) {
        submatrix[0][0] = matrix[1][1];
        submatrix[0][1] = matrix[1][2];
        submatrix[1][0] = matrix[2][1];
        submatrix[1][1] = matrix[2][2];
    } else if (i == 2) {
        submatrix[0][0] = matrix[0][1];
        submatrix[0][1] = matrix[0][2];
        submatrix[1][0] = matrix[2][1];
        submatrix[1][1] = matrix[2][2];
    } else if (i == 3) {
        submatrix[0][0] = matrix[0][1];
        submatrix[0][1] = matrix[0][2];
        submatrix[1][0] = matrix[1][1];
        submatrix[1][1] = matrix[1][2];
    }

    // send submatrix to corresponding client
    if (send(client_socket[i], &submatrix, sizeof(submatrix), 0) < 0) {
        perror("send failed");
        exit(EXIT_FAILURE);
    }
    printf("Sent submatrix %d to client%d\n", i, i);
}


            
  
int det[3];
for (int i = 0; i < 3; i++) {
    // receive determinant from client
    if (recv(client_socket[i+1], &det[i], sizeof(det[i]), 0) < 0) {
        perror("receive failed");
        exit(EXIT_FAILURE);
    }
    printf("Received determinant from client%d\n = %d", i,det[i]);
    //printf("%d",det[0]);
   
}

int determinant = (matrix[0][0]*det[0] - matrix[1][0]*det[1] + matrix[2][0]*det[2]);
    printf("Calculated determinant of matrix: %d\n", determinant);

    // send determinant of matrix to client0
    if (send(client_socket[0], &determinant, sizeof(determinant), 0) < 0) {
        perror("send failed");
        exit(EXIT_FAILURE);
    }
    printf("Sent determinant of matrix to client0\n");

    // close sockets
    for (int i = 0; i < 4; i++) {
        close(client_socket[i]);
    }
    
    
    //writing details in a result txt file
    FILE *fp;
   fp = fopen("result.txt", "w");
   
   fprintf(fp, "%s\n", "Input matrix is: ");
   for(int i=0;i<3;i++){
   for(int j=0;j<3;j++){
    fprintf(fp, "%d ", matrix[i][j]);
   }
    fprintf(fp, "\n");
   }
   
    fprintf(fp, "determinant 1: %d\n", det[0]);
    fprintf(fp, "determinant 2: %d\n", det[1]);
    fprintf(fp, "determinant 3: %d\n", det[2]);
    fprintf(fp, "Final determinant: %d\n",  determinant);
    
   printf("File created and text stored successfully!\n");
    fclose(fp);

    close(server_socket);



    return 0;

}



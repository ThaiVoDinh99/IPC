#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/my_unix_socket"
#define BUFFER_SIZE 256

int main() {
    int server_fd, client_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFFER_SIZE];

    // Create socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Remove old socket file if it exists
    unlink(SOCKET_PATH); 

    // Prepare server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Bind socket to address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on %s...\n", SOCKET_PATH);

    // Accept client connection
    client_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd == -1) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    // Read data from client
    ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read == -1) {
        perror("recv");
    } else {
        buffer[bytes_read] = '\0'; // Null-terminate the received data
        printf("Received from client: %s\n", buffer);
    }

    // Send response to client
    const char *response = "Hello from server!";
    if (send(client_fd, response, strlen(response), 0) == -1) {
        perror("send");
    }

    // Close sockets
    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH); // Clean up socket file
    return 0;
}
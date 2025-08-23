#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/my_unix_socket"
#define BUFFER_SIZE 256

int main() {
    int client_fd;
    struct sockaddr_un server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Prepare server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Connect to server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    // Send data to server
    const char *message = "Hello from client!";
    if (send(client_fd, message, strlen(message), 0) == -1) {
        perror("send");
    }

    // Read response from server
    ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read == -1) {
        perror("recv");
    } else {
        buffer[bytes_read] = '\0'; // Null-terminate the received data
        printf("Received from server: %s\n", buffer);
    }

    // Close socket
    close(client_fd);
    return 0;
}
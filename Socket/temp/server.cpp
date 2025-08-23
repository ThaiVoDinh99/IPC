#include <sys/socket.h>
#include <sys/un.h>
#include <string>
#include <errno.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/thaivodinh"
#define BUFFER_SIZE 256

int main() {
    struct sockaddr_un socket_addr, socket_client_info;
    int f_id = 0;
    int f_bind = 0;
    int f_listen = 0;
    int f_accept = 0;
    char message[BUFFER_SIZE];


    f_id = socket(AF_UNIX, SOCK_STREAM, 0);
    if (f_id == -1) {
        perror("Server 1: ");
        exit(EXIT_FAILURE);
    }

    unlink(SOCKET_PATH);

    memset(&socket_addr, 0, sizeof(socket_addr));
    socket_addr.sun_family = AF_UNIX;
    strncpy(socket_addr.sun_path, SOCKET_PATH, sizeof(socket_addr.sun_path) - 1);

    f_bind = bind(f_id, (const struct sockaddr*)&socket_addr, sizeof(socket_addr));
    if (f_bind == -1) {
        perror("Server 2: ");
        exit(EXIT_FAILURE);
    }

    f_listen = listen(f_id, 2);
    if (f_listen == -1) {
        perror("Server 3: ");
        exit(EXIT_FAILURE);
    }

    printf("Server: Start listening: %s", socket_addr.sun_path);
    fflush(stdout);

    socklen_t socket_client_len = sizeof(socket_client_info);
    f_accept = accept(f_id, (struct sockaddr*)&socket_client_info, &socket_client_len);

    // int size = read(f_id, message, sizeof(BUFFER_SIZE));
    ssize_t f_recv = recv(f_id, message, sizeof(message), 0);
    message[f_recv] = '\0';
    printf("Server read message: %s - %d", message, f_recv);

    
    unlink(SOCKET_PATH);
    close(f_id);
    return 0;
}

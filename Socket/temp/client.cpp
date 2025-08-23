#include <sys/socket.h>
#include <sys/un.h>
#include <string>
#include <errno.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/thaivodinh"
#define BUFFER_SIZE 256

int main() {
    struct sockaddr_un socket_addr;
    int f_id = 0;
    int f_bind = 0;
    int f_connect = 0;
    int f_accept = 0;
    char message[BUFFER_SIZE];


    f_id = socket(AF_UNIX, SOCK_STREAM, 0);
    if (f_id == -1) {
        perror("Client 1: ");
        exit(EXIT_FAILURE);
    }

    // unlink(SOCKET_PATH);

    memset(&socket_addr, 0, sizeof(socket_addr));
    socket_addr.sun_family = AF_UNIX;
    strncpy(socket_addr.sun_path, SOCKET_PATH, sizeof(socket_addr.sun_path) - 1);

    // f_bind = bind(f_id, (const struct sockaddr*)&socket_addr, sizeof(socket_addr));
    // if (f_bind == -1) {
    //     perror("Client 2: ");
    //     exit(EXIT_FAILURE);
    // }

    printf("Client: Start connecting: %s", socket_addr.sun_path);
    f_connect = connect(f_id, (const struct sockaddr*)&socket_addr, sizeof(socket_addr));
    if (f_connect == -1) {
        perror("Client 3: ");
        exit(EXIT_FAILURE);
    }

    strcpy(message, "I'm THAIVD");
    // int f_write = write(f_id, message, sizeof(BUFFER_SIZE));
    ssize_t f_send = send(f_id, message, sizeof(message) - 1, 0);
    printf("Client: write %d", f_send);

    // unlink(SOCKET_PATH);
    close(f_id);
    return 0;
}

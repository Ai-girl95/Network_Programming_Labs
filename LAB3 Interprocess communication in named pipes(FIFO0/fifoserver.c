#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_PATH "/tmp/myfifo"

int main() {
    int fd;
    char message[] = "Hello from the server via FIFO!";

    // Create the FIFO (named pipe) if it does not exist
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        perror("mkfifo");
        // It's okay if the FIFO already exists
    }

    printf("Server: Waiting for client to read...\n");

    // Open the FIFO for writing
    fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write a message to the FIFO
    if (write(fd, message, strlen(message) + 1) == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Server: Message sent to client.\n");

    close(fd);
    // Optionally remove the FIFO after use
    // unlink(FIFO_PATH);

    return 0;
}

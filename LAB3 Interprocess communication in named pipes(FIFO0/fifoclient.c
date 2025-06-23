
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/myfifo"

int main() {
    int fd;
    char buffer[256];

    // Open the FIFO for reading
    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read the message from the FIFO
    if (read(fd, buffer, sizeof(buffer)) == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Client: Received message: %s\n", buffer);

    close(fd);
    // Optionally remove the FIFO after use
    // unlink(FIFO_PATH);

    return 0;
}

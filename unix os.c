#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, n;
    char buffer[100];
    fd = creat("example.txt", 0644);
    if (fd == -1) {
        perror("creat");
        exit(EXIT_FAILURE);
    }
    printf("File created successfully.\n");
    fd = open("example.txt", O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    write(fd, "Hello, world!\n", 14);
    printf("Data written to file.\n");
    close(fd);
    printf("File closed successfully.\n");

    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    n = read(fd, buffer, 100);
    if (n == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    printf("Data read from file: %s\n", buffer);
    close(fd);
    printf("File closed successfully.\n");

    return 0;
}

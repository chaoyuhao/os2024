#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define i64 long long
#define FILE_SIZE ((i64)1024 * 1024 * 1024) // 1GB
#define MMAP_SIZE ((i64)2 * 1024 * 1024 * 1024) // 2GB

int main() {
    int fd;
    char *file_contents;
    char *mapped_contents;

    // Create a temporary file
    fd = open("temp_file", O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    // Set the file size
    if (lseek(fd, FILE_SIZE - 1, SEEK_SET) == -1) {
        close(fd);
        perror("Error calling lseek() to 'stretch' the file");
        exit(EXIT_FAILURE);
    }
    if (write(fd, "", 1) == -1) {
        close(fd);
        perror("Error writing last byte of the file");
        exit(EXIT_FAILURE);
    }

    // Memory map the file
    mapped_contents = mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_contents == MAP_FAILED) {
        close(fd);
        perror("Error mapping the file");
        exit(EXIT_FAILURE);
    }

    // Access the mapped memory
    printf("Memory mapped successfully\n");

    // Clean up
    munmap(mapped_contents, MMAP_SIZE);
    close(fd);
    unlink("temp_file");

    return 0;
}


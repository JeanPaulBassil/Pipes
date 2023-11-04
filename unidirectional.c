// This is the standard unidirectional pipe implementation

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

// Define buffer size for the messages.
#define BUFFER_SIZE 25
// Define read and write end of pipe.
#define READ_END 0
#define WRITE_END 1

int main() {
    // Message to be written to the pipe.
    char writeMsg[BUFFER_SIZE] = "Greetings";
    // Buffer to read the message from the pipe.
    char readMsg[BUFFER_SIZE];
    // File descriptors for the pipe.
    int fd[2];

    // Create a pipe and check for errors.
    if (pipe(fd) == -1) {
        fprintf(stderr, "Error creating the pipe.\n");
        return 1;
    }

    // Fork the current process to create a child process.
    pid_t child = fork();

    // Check for errors in fork().
    if (child < 0) {
        fprintf(stderr, "Error forking child.\n");
        return 1;
    } else if (child > 0) {
        // Parent process: write to the pipe.

        // Close the unused read end of the pipe.
        close(fd[READ_END]);

        // Write the message to the pipe and check for errors.
        if (write(fd[WRITE_END], writeMsg, strlen(writeMsg) + 1) == -1) {
            fprintf(stderr, "Error writing to pipe.\n");
            return 1;
        }

        // Close the write end of the pipe after writing.
        close(fd[WRITE_END]);
    } else {
        // Child process: read from the pipe.

        // Close the unused write end of the pipe.
        close(fd[WRITE_END]);

        // Read the message from the pipe into the buffer.
        if (read(fd[READ_END], readMsg, BUFFER_SIZE) == -1) {
            fprintf(stderr, "Error reading from pipe.\n");
            return 1;
        }

        // Output the read message to stdout.
        printf("Read: %s\n", readMsg);

        // Close the read end of the pipe after reading.
        close(fd[READ_END]);
    }

    return 0;
}

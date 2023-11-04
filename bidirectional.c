// This is the bidirectional pipe implementation


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

// Define the read and write ends of the pipe.
#define READ_END 0
#define WRITE_END 1

int main() {
    // File descriptors for two pipes (for bidirectional communication).
    int fd[2];
    int fd1[2];

    // Create two pipes and check for errors.
    if (pipe(fd) == -1 || pipe(fd1) == -1) {
        fprintf(stderr, "Error creating pipes.\n");
        return 1;
    }

    // Fork the current process to create a child process.
    pid_t child = fork();

    // Check for errors in fork().
    if (child < 0) {
        fprintf(stderr, "Error Forking child.\n");
        return 1;
    } 
    
    if (child == 0) {
        // Child process code.

        // Close the read end of the first pipe and write end of the second (not used by child).
        close(fd[READ_END]);
        close(fd1[WRITE_END]);

        // Prompt user for input.
        printf("Enter a character: ");
        char a;
        scanf("%c", &a);

        // Send character to parent process.
        write(fd[WRITE_END], &a, sizeof(char));
        close(fd[WRITE_END]);

        // Read the transformed data from parent.
        int answer;
        read(fd1[READ_END], &answer, sizeof(int));
        close(fd1[READ_END]);

        // Output the result.
        printf("Casted: %d\n", answer);
    } else {
        // Parent process code.

        // Close the write end of the first pipe and read end of the second (not used by parent).
        close(fd[WRITE_END]);
        close(fd1[READ_END]);

        // Read character sent by child.
        char c;
        read(fd[READ_END], &c, sizeof(char));
        close(fd[READ_END]);

        // Convert character to integer and write it back to child.
        int a = c - '0';
        write(fd1[WRITE_END], &a, sizeof(int));
        close(fd1[WRITE_END]);
    }

    return 0;
}

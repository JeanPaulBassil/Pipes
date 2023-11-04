// Write a C program that forks a child and uses pipe as mean of IPC to
// implement the following command: “ ls | wc – l”
//  The child should execute “ls” and send the output to the parent
//  The parent should execute “wc – l” and returns the results
//  Use dup() for redirecting the standard input and output
// 4 E.g.:
// – output of exec should be redirected to be written to the pipe
// – input of the exec should be redirected to be read from the pipe

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>

#define READ_END 0
#define WRITE_END 1

int main(){

    int fd[2];
    // Create a pipe
    pipe(fd);

    // Fork a child process
    pid_t child = fork();

    // Error handling for fork failure
    if(child < 0){
        fprintf(stderr, "Error forking child.\n");
        return 1;
    }

    if(child == 0){ // Child process
        // Redirect stdout to the pipe write end
        close(1); // Close standard output
        dup(fd[WRITE_END]); // Duplicate write end to standard output
        close(fd[WRITE_END]); // Close original write end
        close(fd[READ_END]); // Close read end not used by child

        // Execute "ls -l"
        char *exp[] = {"ls", "-l", NULL};
        if(execvp("ls", exp) < 0){
            fprintf(stderr, "Error executing the ls command.\n");
            exit(EXIT_FAILURE); // Exit with failure status if exec fails
        }
    } else { // Parent process
        // Wait for child process to complete
        wait(NULL);

        // Redirect stdin to the pipe read end
        close(0); // Close standard input
        dup(fd[READ_END]); // Duplicate read end to standard input
        close(fd[READ_END]); // Close original read end
        close(fd[WRITE_END]); // Close write end not used by parent

        // Execute "wc -l"
        char *exp[] = {"wc", "-l", NULL};
        if(execvp("wc", exp) < 0){
            fprintf(stderr, "Error executing the wc command.\n");
            exit(EXIT_FAILURE); // Exit with failure status if exec fails
        }
    }

    // These close calls will only be executed if execvp fails and exit is not called for some reason.
    close(fd[READ_END]); 
    close(fd[WRITE_END]);
    return 0;
}

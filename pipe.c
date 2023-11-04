// This is the standard unidirectional pipe implementation


#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(){
    char writeMsg[BUFFER_SIZE] = "Greetings";
    char readMsg[BUFFER_SIZE];
    int fd[2];

    if(pipe(fd) == -1){
        printf("Error creating the pipe.\n");
        return 1;
    }

    pid_t child = fork();

    if(child < 0){
        printf("Error forking child.\n");
    } else if (child > 0){
        close(fd[READ_END]);

        write(fd[WRITE_END], writeMsg, strlen(writeMsg) + 1);
        close(fd[WRITE_END]);
    } else {
        close(fd[WRITE_END]);
        read(fd[READ_END], readMsg, BUFFER_SIZE);
        printf("Read: %s\n", readMsg);
        close(fd[READ_END]);
    }
    
    return 0;
}
# Pipes in C

This repository contains three C programs demonstrating the use of UNIX pipes for inter-process communication (IPC). Each file is a standalone program that illustrates a different aspect of pipe usage.

## Files

- `unidirectional.c`: This program shows how to create a unidirectional pipe between a parent and child process, where the parent sends a message to the child process.

- `bidirectional.c`: This program extends the concept to bidirectional communication using two pipes. One pipe sends data from the parent to the child, and the other pipe sends data from the child back to the parent.

- `practice.c`: This file demonstrates the use of pipes to connect the output of one command (`ls -l`) to the input of another command (`wc -l`) in a manner similar to how they would be connected using a shell pipe.

## Usage

To compile and run each program, use the following commands:

```bash
gcc -o unidirectional unidirectional.c
./unidirectional

gcc -o bidirectional bidirectional.c
./bidirectional

gcc -o practice practice.c
./practice
```

Make sure to run these commands in a UNIX-like environment with GCC installed.

## Program Descriptions

### `unidirectional.c`

This program creates a simple unidirectional pipe where the parent process writes a message and the child process reads and prints it.

### `bidirectional.c`

This program uses two pipes to establish bidirectional communication. The child process prompts the user for a character, sends it to the parent, and the parent converts this character to its integer representation and sends it back.

### `practice.c`

This program mimics the behavior of piping commands in the shell. The child process executes `ls -l`, and the parent process takes the output of this command as input and executes `wc -l`, effectively counting the number of lines in the output of `ls -l`.

## Dependencies

- A UNIX-like operating system
- GCC compiler

## Notes

- Error handling is implemented in each program for the respective system calls.
- Standard input and output are redirected using `dup()` in `practice.c` to simulate the behavior of a shell pipe.
- It is essential to close unused file descriptors to prevent resource leakage.
/**
Fork/Exec using pipes (Ch. 3 Processes)

Name: Elisabeth Domond
Course: CPSC 351-02

Description: In the textbook it shows code similar to this one of the parent sending the message, Greetings, to the child. This code, down below, will instead, have the child send the Greetings message to the parent. 

@author Silberschatz, Galvin, and Gagne
Operating System Concepts  - Ninth Edition
Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main(void)
{
	char write_msg[BUFFER_SIZE] = "Greetings";
	char read_msg[BUFFER_SIZE];
	pid_t pid;
	int fd[2];

	/* create the pipe */
	if (pipe(fd) == -1) {
		fprintf(stderr,"Pipe failed");
		return 1;
	}

	/* now fork a child process */
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}

	if (pid == 0) {  /* child process */
		/* close the unused end of the pipe */
		close(fd[READ_END]);

		printf("child end of pipe--sending: %s\n", write_msg);
		/* write to the pipe */
		write(fd[WRITE_END], write_msg, strlen(write_msg)+1); 	
		/* close the write end of the pipe */
		close(fd[WRITE_END]);
	}
	else { /* parent process */
		/* close the unused end of the pipe */
		close(fd[WRITE_END]);

		/* read from the pipe */
		read(fd[READ_END], read_msg, BUFFER_SIZE);
		printf("parent end of pipe--received: %s\n",read_msg);

		/* close the write end of the pipe */
		close(fd[READ_END]);
	}

	return 0;
}

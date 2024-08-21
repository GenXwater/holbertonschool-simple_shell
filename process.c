#include "main.h"

/**
 * get_process_ids - Prints the current PID and PPID
 */
void get_process_ids(void)
{
	pid_t my_pid;
	pid_t my_ppid;

	my_pid = getpid();
	my_ppid = getppid();
	printf("PID: %u\n", my_pid);
	printf("PPID: %u\n", my_ppid);
}

/**
 * fork_and_wait - Example function for creating a process and waiting for it
 */
void fork_and_wait(void)
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		return;
	}
	if (child_pid == 0)
	{
		/* Simulate some work in child process */
		printf("Child process\n");
		// Removed sleep, add any other work here if needed
		_exit(0);  /* Use _exit to exit without cleanup for the child process */
	}
	else
	{
		wait(&status);
		printf("Child process ended\n");
	}
}


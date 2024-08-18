#include "main.h"

/**
 * split_string_to_av - Splits a string into an array of words
 * @str: The string to split
 * @argv: The array to store the words
 * @max_args: Maximum number of arguments
 *
 * Description: Uses strtok to split the input string into words, storing each
 * word in the argv array. The function limits the number of arguments to
 * max_args - 1 to leave space for a NULL terminator.
 */
void split_string_to_av(char *str, char *argv[], int max_args)
{
	int i = 0;
	char *token;

	token = strtok(str, " \t\n");
	while (token && i < max_args - 1)
	{
		argv[i] = token;
		i++;
		token = strtok(NULL, " \t\n");
	}
	argv[i] = NULL;
}

/**
 * execute_command - Executes a command with its arguments
 * @argv: Array of command and arguments
 * @envp: Environment variables
 *
 * Description: This function forks a process and executes a command using
 * execve. The parent process waits for the child to finish.
 */
void execute_command(char *argv[], char *envp[])
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		if (execve(argv[0], argv, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}


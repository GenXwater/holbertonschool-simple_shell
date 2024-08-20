#include "main.h"

/**
 * split_string_to_av - Splits a string into an array of words
 * @str: The string to split
 * @argv: The array to store the words
 * @max_args: Maximum number of arguments
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

/**
 * handle_builtin_commands - Handles the built-in commands for the shell
 * @cmd_argv: Array of command arguments
 * @envp: Environment variables
 *
 * Return: 1 if a built-in command was executed, 0 otherwise
 */
int handle_builtin_commands(char *cmd_argv[], char *envp[])
{
	if (strcmp(cmd_argv[0], "exit") == 0)
	{
		exit(0);
	}
	else if (strcmp(cmd_argv[0], "printenv") == 0)
	{
		print_environment(envp);
		return (1);
	}
	else if (strcmp(cmd_argv[0], "setenv") == 0 && cmd_argv[1] && cmd_argv[2])
	{
		_setenv(cmd_argv[1], cmd_argv[2], 1, envp);
		return (1);
	}
	else if (strcmp(cmd_argv[0], "unsetenv") == 0 && cmd_argv[1])
	{
		_unsetenv(cmd_argv[1], envp);
		return (1);
	}
	else if (strcmp(cmd_argv[0], "showpath") == 0)
	{
		print_path_directories(envp);
		return (1);
	}
	else if (strcmp(cmd_argv[0], "man") == 0 && cmd_argv[1] &&
			strcmp(cmd_argv[1], "simple_shell") == 0)
	{
		char *man_command[] = {"/bin/man", "./simple-shell.1", NULL};

		execute_man_command(man_command);
		return (1);
	}
	return (0);
}

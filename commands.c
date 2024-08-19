#include "main.h"

/**
 * split_string_to_av - Splits a string into an array of words
 * @str: The string to split
 * @argv: The array to store the words
 * @max_args: Maximum number of arguments
 *
 * Description: Uses strtok to split the input string into words,
 * storing each word in the argv array. The function limits the number
 * of arguments to max_args - 1 to leave space for a NULL terminator.
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
 * find_executable_in_path - Finds the full path of an executable in the PATH
 * @command: The command to find
 * @path_copy: A copy of the PATH variable
 *
 * Return: The full path of the executable, or NULL if not found
 */
char *find_executable_in_path(const char *command, char *path_copy)
{
	char *dir;
	char *full_path;
	struct stat st;

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (!full_path)
		{
			perror("malloc");
			return (NULL);
		}

		sprintf(full_path, "%s/%s", dir, command);

		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	return (NULL);
}

/**
 * get_command_full_path - Gets the full path of the command
 * @argv: Array of command and arguments
 * @envp: Environment variables
 *
 * Return: The full path of the command, or NULL if not found
 */

char *get_command_full_path(char *argv[], char *envp[])
{
	char *full_path = NULL;
	char *path_copy = NULL;

	if (strchr(argv[0], '/') != NULL)
	{
		full_path = argv[0];
	}
	else
	{
		path_copy = strdup(_getenv("PATH", envp));
		full_path = find_executable_in_path(argv[0], path_copy);

		if (full_path == NULL)
		{
			fprintf(stderr, "%s: command not found\n", argv[0]);
		}

		free(path_copy);
	}

	return (full_path);
}

/**
 * fork_and_execute - Forks and executes a command
 * @full_path: The full path to the executable
 * @argv: Array of command and arguments
 * @envp: Environment variables
 */
void fork_and_execute(char *full_path, char *argv[], char *envp[])
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		if (full_path != argv[0])
			free(full_path);
		return;
	}

	if (pid == 0)
	{
		if (execve(full_path, argv, envp) == -1)
		{
			perror("execve");
			if (full_path != argv[0])
				free(full_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}

	if (full_path != argv[0])
		free(full_path);
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
	char *full_path = get_command_full_path(argv, envp);

	if (full_path != NULL)
	{
		fork_and_execute(full_path, argv, envp);
	}
}


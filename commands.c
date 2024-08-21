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
 * find_executable_in_path - Finds an executable in the PATH
 * @command: The command to find
 * @path: The PATH environment variable
 *
 * Return: Full path to the executable if found, otherwise NULL
 */
char *find_executable_in_path(char *command, char *path)
{
	char *dir;
	char *full_path = malloc(4096); /* Maximum length for a path */
	struct stat st;

	if (!full_path)
	{
		perror("malloc");
		return (NULL);
	}

	dir = strtok(path, ":");
	while (dir)
	{
		sprintf(full_path, "%s/%s", dir, command);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
			return (full_path);
		dir = strtok(NULL, ":");
	}

	printf("find_executable_in_path: command '%s' not found in PATH\n", command);
	free(full_path);
	return (NULL);
}

/**
 * get_full_path - Retrieves the full path of a command
 * @command: The command to find
 * @envp: Environment variables
 *
 * Return: Full path to the command if found, otherwise NULL
 */
char *get_full_path(char *command, char *envp[])
{
	char *path = _getenv("PATH", envp);
	char *path_copy, *full_path;

	if (!path)
	{
		printf("get_full_path: PATH variable not found\n");
		return (NULL);
	}

	path_copy = malloc(strlen(path) + 1);
	if (!path_copy)
	{
		perror("malloc");
		return (NULL);
	}
	copy_string(path_copy, path);

	full_path = find_executable_in_path(command, path_copy);
	free(path_copy);

	return (full_path);
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
	char *full_path = (argv[0][0] == '/')
		? argv[0] : get_full_path(argv[0], envp);

	if (!full_path)
	{
		printf("execute_command: command '%s' not found\n", argv[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		if (execve(full_path, argv, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		if (full_path != argv[0])
			free(full_path);
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

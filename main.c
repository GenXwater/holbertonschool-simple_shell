#include "main.h"

/**
 * main - Entry point of the simple shell
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environment variables
 *
 * Return: Always 0.
 */
int main(int argc, char *argv[], char *envp[])
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *cmd_argv[10];
	int max_args = 10;

	(void)argc;  /* Marking unused parameters */
	(void)argv;

	while (1)
	{
		printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			printf("\n");
			break;
		}
		line[strcspn(line, "\n")] = 0;  /* Remove the newline character */
		split_string_to_av(line, cmd_argv, max_args);

		if (cmd_argv[0] == NULL)
			continue;

		if (handle_builtin_commands(cmd_argv, envp) == 1)
			continue;

		execute_command(cmd_argv, envp);
	}

	free(line);
	return (0);
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

/**
 * execute_man_command - Executes the man command
 * @man_command: Array containing the man command and its arguments
 */
void execute_man_command(char *man_command[])
{
	if (fork() == 0)
	{
		execvp(man_command[0], man_command);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

/**
 * display_man_page - Displays the man page for the simple shell
 * @filename: The name of the man file to display
 */
void display_man_page(const char *filename)
{
	int fd;
	char buffer[1024];
	ssize_t bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return;
	}

	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';  /* Null-terminate the buffer */
		printf("%s", buffer);
	}

	if (bytes_read == -1)
	{
		perror("read");
	}

	close(fd);
}

/**
 * free_resources - Free allocated resources
 * @cmd_argv: Array of command arguments
 * @line: Input line to be freed
 */
void free_resources(char *cmd_argv[], char *line)
{
	int i;

	for (i = 0; cmd_argv[i]; i++)
	{
		free(cmd_argv[i]);
	}

	free(line);
}


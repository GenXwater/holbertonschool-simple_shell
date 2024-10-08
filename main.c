#include "main.h"

/**
 * string_length - Calculates the length of a string
 * @str: The string to measure
 *
 * Return: The length of the string
 */
int string_length(const char *str)
{
	int len = 0;

	while (str[len] != '\0')
		len++;

	return (len);
}

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
	int interactive = isatty(0);

	(void)argc;  /* Marking unused parameters */
	(void)argv;

	while (1)
	{
		if (interactive)
			printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			printf("\n");
			break; /* Handle EOF (Ctrl+D) */
		}

		/* Remove the newline character manually */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

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


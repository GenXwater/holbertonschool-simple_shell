#include "main.h"

/**
 * read_input - Reads the input from the user.
 * @line: Pointer to the buffer that will store the input.
 * @len: Pointer to the size of the buffer.
 */
void read_input(char **line, size_t *len)
{
	ssize_t nread;

	if (isatty(STDIN_FILENO))
		printf("$ ");

	nread = getline(line, len, stdin);
	if (nread == -1)
	{
		printf("\n");
		exit(0); /* Handle EOF (Ctrl+D) */
	}

	/* Remove the newline character */
	(*line)[strcspn(*line, "\n")] = '\0';
}

/**
 * process_command - Processes and executes the input command.
 * @line: The input line.
 * @cmd_argv: Array to store the command arguments.
 * @max_args: Maximum number of arguments.
 * @envp: Environment variables.
 */
void process_command(char *line, char *cmd_argv[], int max_args, char *envp[])
{
	split_string_to_av(line, cmd_argv, max_args);

	if (cmd_argv[0] == NULL)
		return;

	if (strchr(cmd_argv[0], ' ') != NULL)
	{
		fprintf(stderr, "%s: No arguments allowed\n", cmd_argv[0]);
		return;
	}

	if (handle_builtin_commands(cmd_argv, envp) == 1)
		return;

	execute_command(cmd_argv, envp);
}

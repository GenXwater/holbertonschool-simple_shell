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
	int i;
	ssize_t nread;
	char *cmd_argv[2]; /* Only one word, no arguments */
	int max_args = 1;
	(void)argc;  /* Marking unused parameters */
	(void)argv;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			printf("\n");
			break; /* Handle EOF (Ctrl+D) */
		}
		for (i = 0; i < nread; i++)
			for (i = 0; i < nread; i++)
			{
				if (line[i] == '\n')
				{
					line[i] = '\0';
					break;
				}
			}
		split_string_to_av(line, cmd_argv, max_args);
		if (cmd_argv[0] == NULL)
			continue;
		if (strchr(cmd_argv[0], ' ') != NULL)
		{
			fprintf(stderr, "%s: No arguments allowed\n", argv[0]);
			continue;
		}
		execute_command(cmd_argv, envp);
	}
	free(line);
	return (0);
}

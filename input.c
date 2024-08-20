#include "main.h"

/**
 * process_command - Processes a command by checking built-ins or executing it
 * @line: The command line input
 * @envp: The environment variables
 */
void process_command(char *line, char *envp[])
{
	char *cmd_argv[10];
	int max_args = 10;

	split_string_to_av(line, cmd_argv, max_args);

	if (cmd_argv[0] == NULL)
		return;

	if (handle_builtin_commands(cmd_argv, envp) == 1)
		return;

	execute_command(cmd_argv, envp);
}


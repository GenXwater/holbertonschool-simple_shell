#include "main.h"

/**
 * execute_man_command - Executes the man command
 * @man_command: Array containing the man command and its arguments
 */
void execute_man_command(char *man_command[])
{
	pid_t pid;
	char *envp[] = {NULL};  /* Environnement vide pour execve */

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		if (execve(man_command[0], man_command, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
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

	if (close(fd) == -1)
	{
		perror("close");
	}
}

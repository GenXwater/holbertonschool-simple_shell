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
        if (strcmp(cmd_argv[0], "exit") == 0)
        {
            break;
        }
        else if (strcmp(cmd_argv[0], "printenv") == 0)
        {
            print_environment(envp);
        }
        else if (strcmp(cmd_argv[0], "setenv") == 0 && cmd_argv[1] && cmd_argv[2])
        {
            _setenv(cmd_argv[1], cmd_argv[2], 1, envp);
        }
        else if (strcmp(cmd_argv[0], "unsetenv") == 0 && cmd_argv[1])
        {
            _unsetenv(cmd_argv[1], envp);
        }
        else if (strcmp(cmd_argv[0], "showpath") == 0)
        {
            print_path_directories(envp);
        }
        else if (strcmp(cmd_argv[0], "man") == 0 && cmd_argv[1] && strcmp(cmd_argv[1], "simple_shell") == 0)
        {
            display_man_page();
        }
        else
        {
            execute_command(cmd_argv, envp);
        }
    }
    free(line);
    return (0);
}
/**
 * display_man_page - Display the manual page for simple_shell
 */
void display_man_page(void)
{
    int fd;
    char buffer[1024];
    ssize_t bytes_read;
    fd = open("simple_shell.1", O_RDONLY);
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









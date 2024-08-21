#include "main.h"

/**
 * find_executable_in_path - Finds an executable in the PATH
 * @command: The command to find
 * @path: The PATH environment variable
 *
 * Return: Full path to the executable if found, otherwise NULL
 */
char *find_executable_in_path(const char *command, const char *path)
{
    char *dir;
    char *full_path;
    struct stat st;
    char *path_copy = strdup(path);
    char *saveptr;

    if (!path_copy)
        return NULL;

    full_path = malloc(4096); /* Maximum length for a path */
    if (!full_path)
    {
        free(path_copy);
        return NULL;
    }

    dir = strtok_r(path_copy, ":", &saveptr);
    while (dir)
    {
        snprintf(full_path, 4096, "%s/%s", dir, command);
        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
        {
            free(path_copy);
            return full_path;
        }
        dir = strtok_r(NULL, ":", &saveptr);
    }

    free(full_path);
    free(path_copy);
    return NULL;
}

/**
 * execute_man_command - Executes the man command
 * @man_command: Array containing the man command and its arguments
 */
void execute_man_command(char *man_command[])
{
    char *path = _getenv("PATH", environ); /* Fetch PATH environment variable */
    char *full_path;
    char *argv[] = {man_command[0], man_command[1], NULL}; /* Argument array for execve */
    
    if (!path)
    {
        fprintf(stderr, "PATH environment variable not found\n");
        return;
    }

    full_path = find_executable_in_path(man_command[0], path);
    if (!full_path)
    {
        fprintf(stderr, "%s: command not found\n", man_command[0]);
        return;
    }

    if (fork() == 0)
    {
        execve(full_path, argv, environ); /* Execute the command */
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL); /* Wait for the child process to complete */
    }

    free(full_path);
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


#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * command_is_path - Checks if the command uses an explicit path syntax.
 *
 * @command: Command to be checked.
 *
 * Return: 1 if command uses an explicit path syntax,
 * -1 if the command is a wrong path, 0 otherwise.
 */
int command_is_path(const char *command)
{
    if (!command)
        return -1;

    if (command[0] == '/' || command[0] == '.')
    {
        return access(command, X_OK) == 0 ? 1 : -1;
    }
    return 0;
}

/**
 * check_paths - Searches for the command inside the PATH and returns
 * the precise path of the command if found.
 *
 * @command: Command to be searched in the PATH.
 * @argv: Array of arguments sent by main().
 *
 * Return: Precise path of the command if found, NULL otherwise.
 */
char *check_paths(const char *command, char **argv)
{
    char *path = _getenv("PATH");
    if (!path)
    {
        fprintf(stderr, "%s: 127: %s: not found\n", argv[0], command);
        return NULL;
    }

    char *cp_path = strdup(path);
    if (!cp_path)
        return NULL;

    char **paths = tokenizer(cp_path, ":");
    if (!paths)
    {
        free(cp_path);
        return NULL;
    }

    char *check_path = NULL;
    for (int i = 0; paths[i]; i++)
    {
        size_t len = strlen(paths[i]) + strlen(command) + 2;
        check_path = malloc(len);
        if (!check_path)
        {
            clean(cp_path, paths);
            return NULL;
        }
        snprintf(check_path, len, "%s/%s", paths[i], command);
        if (access(check_path, X_OK) == 0)
        {
            clean(cp_path, paths);
            return check_path;
        }
        free(check_path);
    }

    fprintf(stderr, "%s: 1: %s: not found\n", argv[0], command);
    clean(cp_path, paths);
    return NULL;
}

/**
 * check_command - Checks if the command is either an explicit path or
 * can be found inside the PATH environment variable.
 *
 * @command: Command to be checked.
 * @argv: Array containing the arguments sent by main().
 *
 * Return: Command if it's a valid explicit path, path of the command if found,
 * NULL otherwise.
 */
char *check_command(char *command, char **argv)
{
    if (!command)
        return NULL;

    int path_status = command_is_path(command);
    if (path_status == 1)
        return command;
    else if (path_status == -1)
    {
        fprintf(stderr, "%s: 1: %s: not found\n", argv[0], command);
        free(command);
        return NULL;
    }

    char *right_path = check_paths(command, argv);
    if (right_path)
        return right_path;

    return NULL;
}


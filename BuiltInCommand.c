#include "shell.h"

/**
 * check_builtin - Checks if a command is a built-in command and executes it if so.
 *
 * @command: The command to be checked.
 * @argv: The arguments array.
 *
 * Return: 1 if the command is not a built-in or if the built-in command
 * is successfully executed, 0 otherwise.
 */
int check_builtin(char *command, char **argv)
{
    if (strcmp(command, "exit") == 0) {
        exit_func(argv);
        return 1;
    } else if (strcmp(command, "env") == 0 || strcmp(command, "printenv") == 0) {
        printenv_func();
        return 1;
    }
    return 0;
}

/**
 * exit_func - Implements the 'exit' built-in command.
 *
 * @argv: The arguments array.
 */
void exit_func(char **argv)
{
    clean(NULL, argv);
    exit(0);
}

/**
 * printenv_func - Implements the 'printenv' built-in command.
 */
void printenv_func()
{
    extern char **environ;
    char **env = environ;

    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
}

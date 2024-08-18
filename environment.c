#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * check_builtin - Checks if an input is a builtin command and executes it if so.
 *
 * @arg: The command to be checked and executed if it's a builtin command.
 * @temp: Buffer containing the command.
 *
 * Return: 1 if a builtin command is executed, 0 otherwise.
 */
int check_builtin(char **arg, char *temp)
{
    if (!*arg)
        return 0;

    if (strcmp(*arg, "exit") == 0)
    {
        exit_func(arg, temp);
        return 1;
    }
    else if (strcmp(*arg, "env") == 0 || strcmp(*arg, "printenv") == 0)
    {
        printenv_func(arg, temp);
        return 1;
    }

    return 0;
}

/**
 * exit_func - Builtin command that exits the shell after cleaning the memory.
 *
 * @arg: Arguments to be cleaned before exit.
 * @temp: Buffer to be cleaned before exit.
 */
void exit_func(char **arg, char *temp)
{
    clean(temp, arg);
    exit(0);
}

/**
 * printenv_func - Builtin command that prints the current environment of the process.
 *
 * @arg: Not used.
 * @temp: Not used.
 */
void printenv_func(char **arg, char *temp)
{
    extern char **environ;
    char **env = environ;

    (void)arg;
    (void)temp;

    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}


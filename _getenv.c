#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _getenv - Searches for a specific environment variable
 * and returns its value if found.
 *
 * @env_variable: Environment variable to be searched
 *
 * Return: The value of the environment variable if found,
 * NULL otherwise.
 */
char *_getenv(char *env_variable)
{
    // Variable to store the value of the environment variable
    char *value = NULL;

    // Loop through each environment variable
    for (char **env = environ; *env != NULL; env++) {
        // Find the position of '=' character in the current environment variable
        char *eq_pos = strchr(*env, '=');

        // If '=' character is found and matches the given environment variable
        if (eq_pos != NULL && strncmp(*env, env_variable, eq_pos - *env) == 0) {
            // Allocate memory for the value of the environment variable
            value = malloc(strlen(eq_pos + 1) + 1);
            if (value == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }

            // Copy the value part of the environment variable
            strcpy(value, eq_pos + 1);

            // Exit the loop after finding the environment variable
            break;
        }
    }

    return value;
}

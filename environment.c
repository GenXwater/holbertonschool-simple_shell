#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * _getenv - Custom function to get the value of an environment variable
 * @name: Name of the environment variable
 * @envp: Environment variables
 *
 * Return: Ptr to the value of the environment variable, or NULL if not found
 */
char *_getenv(const char *name, char *envp[])
{
	int i = 0;
	size_t len = strlen(name);

	while (envp[i])
	{
		if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			return (envp[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

/**
 * print_environment - Prints all environment variables
 * @envp: Environment variables
 */
void print_environment(char *envp[])
{
	int i = 0;

	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

/**
 * _setenv - Custom implementation of setenv
 * @name: Name of the environment variable
 * @value: Value of the environment variable
 * @overwrite: Flag to indicate if existing value should be overwritten
 * @envp: Environment variables
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite, char *envp[])
{
	int i = 0;
	size_t len = strlen(name);
	char *new_env;

	while (envp[i])
	{
		if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			if (!overwrite)
				return (0);

			free(envp[i]);
			break;
		}
		i++;
	}

	new_env = malloc(strlen(name) + strlen(value) + 2);
	if (!new_env)
	{
		perror("malloc");
		return (-1);
	}

	sprintf(new_env, "%s=%s", name, value);
	envp[i] = new_env;
	envp[i + 1] = NULL;

	return (0);
}

/**
 * _unsetenv - Custom implementation of unsetenv
 * @name: Name of the environment variable to remove
 * @envp: Environment variables
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name, char *envp[])
{
	int i = 0;
	size_t len = strlen(name);

	while (envp[i])
	{
		if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			free(envp[i]);
			while (envp[i])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			return (0);
		}
		i++;
	}

	printf("_unsetenv: %s not found\n", name);
	return (-1);
}

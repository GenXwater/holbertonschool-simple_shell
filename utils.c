#include "main.h"

/**
 * print_path_directories - Prints each directory in the PATH environment variable
 * @envp: Environment variables
 */
void print_path_directories(char *envp[])
{
	char *path = _getenv("PATH", envp);
	char *dir;

	if (!path)
		return;

	path = strdup(path);
	dir = strtok(path, ":");

	while (dir)
	{
		printf("%s\n", dir);
		dir = strtok(NULL, ":");
	}

	free(path);
}

/**
 * build_path_list - Builds a linked list of directories in PATH
 * @envp: Environment variables
 *
 * Return: Pointer to the head of the list, or NULL on error
 */
list_t *build_path_list(char *envp[])
{
	char *path = _getenv("PATH", envp);
	char *dir;
	list_t *head = NULL, *new_node, *last;

	if (!path)
		return (NULL);

	path = strdup(path);
	dir = strtok(path, ":");

	while (dir)
	{
		new_node = malloc(sizeof(list_t));
		if (!new_node)
		{
			free_list(head);
			return (NULL);
		}

		new_node->dir = strdup(dir);
		new_node->next = NULL;

		if (!head)
			head = new_node;
		else
			last->next = new_node;

		last = new_node;
		dir = strtok(NULL, ":");
	}

	free(path);
	return (head);
}

/**
 * free_list - Frees a linked list of directories
 * @head: Pointer to the head of the list
 */
void free_list(list_t *head)
{
	list_t *current, *next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->dir);
		free(current);
		current = next;
	}
}


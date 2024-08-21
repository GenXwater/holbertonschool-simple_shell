#include "main.h"

/**
 * copy_string - Copies a string manually
 * @dest: The destination buffer
 * @src: The source string
 */
void copy_string(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

/**
 * print_path_directories - Prints each directory in the PATH env variable
 * @envp: Environment variables
 */
void print_path_directories(char *envp[])
{
	char *path = _getenv("PATH", envp);
	char *dir;
	char *path_copy;

	if (!path)
		return;

	path_copy = malloc(string_length(path) + 1);
	if (!path_copy)
		return;

	copy_string(path_copy, path);

	dir = strtok(path_copy, ":");

	while (dir)
	{
		printf("%s\n", dir);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
}

/**
 * create_path_node - Creates a new node for the PATH list
 * @dir: Directory to store in the node
 *
 * Return: Pointer to the new node, or NULL on error
 */
list_t *create_path_node(char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);

	new_node->dir = malloc(string_length(dir) + 1);
	if (!new_node->dir)
	{
		free(new_node);
		return (NULL);
	}

	copy_string(new_node->dir, dir);
	new_node->next = NULL;

	return (new_node);
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
	char *path_copy;
	list_t *head = NULL, *new_node, *last = NULL;

	if (!path)
		return (NULL);

	path_copy = malloc(string_length(path) + 1);
	if (!path_copy)
		return (NULL);

	copy_string(path_copy, path);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		new_node = create_path_node(dir);
		if (!new_node)
		{
			free(path_copy);
			free_path_list(head);
			return (NULL);
		}

		if (!head)
			head = new_node;
		else
			last->next = new_node;

		last = new_node;
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (head);
}

/**
 * free_path_list - Frees a linked list of PATH directories
 * @head: Pointer to the head of the list
 */
void free_path_list(list_t *head)
{
	list_t *tmp;

	while (head)
	{
		tmp = head->next;
		free(head->dir);
		free(head);
		head = tmp;
	}
}

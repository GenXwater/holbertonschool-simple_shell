#include "main.h"

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

    /* Allocate memory for path_copy and copy the PATH variable */
    path_copy = malloc(strlen(path) + 1);
    if (!path_copy)
        return;
    strcpy(path_copy, path);

    dir = strtok(path_copy, ":");

    while (dir)
    {
        printf("%s\n", dir);
        dir = strtok(NULL, ":");
    }

    free(path_copy);  /* Free the allocated memory */
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
    list_t *head = NULL, *new_node, *last;

    if (!path)
        return (NULL);

    /* Allocate memory for path_copy and copy the PATH variable */
    path_copy = malloc(strlen(path) + 1);
    if (!path_copy)
        return (NULL);
    strcpy(path_copy, path);

    dir = strtok(path_copy, ":");

    while (dir)
    {
        new_node = malloc(sizeof(list_t));
        if (!new_node)
        {
            free(path_copy);
            return (NULL);
        }

        new_node->dir = malloc(strlen(dir) + 1);
        if (!new_node->dir)
        {
            free(new_node);
            free(path_copy);
            return (NULL);
        }
        strcpy(new_node->dir, dir);
        new_node->next = NULL;

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


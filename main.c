#include "main.h"

/**
 * main - Simple shell that executes commands
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *argv[2];

	while (1)
	{
		printf("#cisfun$ "); /* Affiche le prompt */
		nread = getline(&line, &len, stdin); /* Lit l'entrée utilisateur */

		if (nread == -1) /* Handle end-of-file condition (Ctrl+D) */
		{
			free(line);
			exit(0);
		}

		line[strcspn(line, "\n")] = 0; /* Retire le caractère de nouvelle ligne */

		if (strlen(line) == 0) /* Si l'utilisateur appuie juste sur "Entrée", affiche à nouveau le prompt */
			continue;

		argv[0] = line;
		argv[1] = NULL;

		if (fork() == 0) /* Crée un processus enfant pour exécuter la commande */
		{
			execve(argv[0], argv, NULL); /* Remplace le processus enfant par le nouveau programme */
			perror("./shell"); /* Si execve échoue, affiche une erreur */
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL); /* Le processus parent attend que l'enfant termine */
		}
	}

	free(line);
	return (0);
}

#include stdio.h
#include stdlib.h
#include string.h

#define MAX_TOK 64  // Nombre maximum de tokens, ajustez si nécessaire

/**
 * tokenizer - Divise une chaîne d'entrée en un tableau de tokens en utilisant un délimiteur.
 *
 * @temp: Tampon contenant la chaîne à tokeniser.
 * @delim: Délimiteur utilisé pour séparer les tokens.
 *
 * Return: Tableau de chaînes contenant les tokens, ou NULL en cas d'erreur.
 */
char **tokenizer(char *temp, const char *delim)
{
    char **args = NULL;
    char *token;
    int i = 0;

    if (!temp || !delim)
        return NULL;

    // Allouer la mémoire pour le tableau de tokens
    args = malloc(sizeof(char *) * MAX_TOK);
    if (!args)
        return NULL;

    // Diviser la chaîne en tokens
    token = strtok(temp, delim);
    while (token && i < MAX_TOK - 1)
    {
        args[i] = strdup(token);
        if (!args[i])
        {
            // En cas d'échec d'allocation, libérer la mémoire et retourner NULL
            for (int j = 0; j < i; j++)
                free(args[j]);
            free(args);
            return NULL;
        }
        i++;
        token = strtok(NULL, delim);
    }
    // Ajouter un pointeur NULL à la fin du tableau
    args[i] = NULL;

    return args;
}

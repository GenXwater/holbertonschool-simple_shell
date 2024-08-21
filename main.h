#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * struct list_s - Singly linked list structure for PATH directories
 * @dir: Directory path
 * @next: Pointer to the next node in the list
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

void split_string_to_av(char *str, char *argv[], int max_args);
char *_getenv(const char *name, char *envp[]);
void print_environment(char *envp[]);
int _setenv(const char *name, const char *value, int overwrite, char *envp[]);
int _unsetenv(const char *name, char *envp[]);
void execute_command(char *argv[], char *envp[]);
int handle_builtin_commands(char *cmd_argv[], char *envp[]);
char *find_executable_in_path(char *command, char *path);
char *get_full_path(char *command, char *envp[]);
void execute_man_command(char *man_command[]);
void display_man_page(const char *filename);
void process_command(char *line, char *envp[]);
void get_process_ids(void);
void fork_and_wait(void);
void print_path_directories(char *envp[]);
list_t *build_path_list(char *envp[]);
void free_path_list(list_t *head);
list_t *create_path_node(char *dir);
int string_length(char *str);
void copy_string(char *dest, char *src);

#endif

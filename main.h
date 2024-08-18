
#ifndef MAIN_H
#define MAIN_H
/* Standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* Definition of list_t struct */
typedef struct list_s
{
    char *dir;
    struct list_s *next;
} list_t;
/* Function prototypes */
void split_string_to_av(char *str, char *argv[], int max_args);
char *_getenv(const char *name, char *envp[]);
void print_path_directories(char *envp[]);
list_t *build_path_list(char *envp[]);
int _setenv(const char *name, const char *value, int overwrite, char *envp[]);
int _unsetenv(const char *name, char *envp[]);
void execute_command(char *argv[], char *envp[]);
void print_environment(char *envp[]);
void get_process_ids(void);
void fork_and_wait(void);
void display_man_page(void);
#endif /* MAIN_H */

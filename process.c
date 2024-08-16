#include "main.h"/**
 * get_process_ids - Prints the current PID and PPID
 */
void get_process_ids(void)
{
    pid_t my_pid;
    pid_t my_ppid;    my_pid = getpid();     /* Get the process ID */
    my_ppid = getppid();   /* Get the parent process ID */    printf("PID: %u\n", my_pid);
    printf("PPID: %u\n", my_ppid);
}/**
 * fork_and_wait - Example function for creating a process and waiting for it
 */
void fork_and_wait(void)
{
    pid_t child_pid;
    int status;    child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork");
        return;
    }    if (child_pid == 0)
    {
        printf("Child process\n");
        sleep(2);  /* Simulate work in the child process */
    }
    else
    {
        wait(&status);  /* Wait for the child process to finish */
        printf("Child process ended\n");
    }
}

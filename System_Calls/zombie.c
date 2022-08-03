/*******************************************************************************************************************
 * Program to demonstrate the creation of a zombie process.
 * A Zombie process is a a process that has completed execution but still has an entry in the process table.
 * The following system calls are used to demonstrate the zombie process:
 *     =>  pid_t getpid() returns the process ID (PID) of the calling process.
 *     =>  pid_t getppid() returns the process ID of the parent of the calling process.
 *     =>  pid_t wait(int *wstatus) suspends execution of the calling thread until one of its children terminates.
 *     =>  sleep() causes the calling thread to sleep either: 
           1) Until the number of real-time seconds specified in seconds have elapsed or
           2) Until a signal arrives which is not ignored.
           Prototype: unsigned int sleep(unsigned int seconds)
*******************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main() {
    pid_t my_pid, child_pid, parent_pid;
    child_pid = fork();
    if (child_pid < 0) {
        printf("\nFork failed, exiting!!\n");
        exit(1);
    }

    if (child_pid == 0) {
        // This is the child process part
        printf("\n[CHILD] This is the child process.\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[CHILD] My pid is %d\n", my_pid);
        printf("[CHILD] My parent's pid is %d\n", parent_pid);
        printf("[CHILD] Exiting\n");
        exit(1);
    } else {
        // This is the parent process part
        printf("\n[PARENT] This is the parent process\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[PARENT] My pid is %d\n", my_pid);
        printf("[PARENT] My parent's pid is %d\n", parent_pid);
        printf("[PARENT] Sleeping for 10 seconds\n");
        sleep(10);
        printf("\n[PARENT] Child process with pid = %d has ended, but still has an entry in the process table.\n", child_pid);
        printf("[PARENT] It is therefore a Zombie process\n");
    }
    return 0;
}
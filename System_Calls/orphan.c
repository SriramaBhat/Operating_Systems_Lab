/***********************************************************************************************************************
 * Program to demonstrate the creation of a orphan process.
 * Orphan process is a process whose parent process has finished or terminated, though it remains running itself.
 * The following system calls are used to demonstrate the zombie process:
 *     =>  pid_t getpid() returns the process ID (PID) of the calling process.
 *     =>  pid_t getppid() returns the process ID of the parent of the calling process.
 *     =>  pid_t wait(int *wstatus) suspends execution of the calling thread until one of its children terminates.
 *     =>  sleep() causes the calling thread to sleep either: 
           1) Until the number of real-time seconds specified in seconds have elapsed or
           2) Until a signal arrives which is not ignored.
           Prototype: unsigned int sleep(unsigned int seconds)
************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main() {
    pid_t my_pid, parent_pid, child_pid;
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
        printf("[CHILD] Sleeping for 10 seconds\n");
        sleep(10);
        printf("\n[CHILD] My parent has ended, so I am an orphan process, adopted by init process\n");
    } else {
        // This is the parent process part
        printf("\n[PARENT] This is the parent process.\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[PARENT] My pid is %d\n", my_pid);
        printf("[PARENT] My parent's pid is %d\n", parent_pid);
        printf("[PARENT] Exiting\n");
        exit(0);
    }
    
    return 0;
}
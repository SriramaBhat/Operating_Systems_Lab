/***********************************************************************************************************************
 * Program to illustrate the creation, execution and termination of the processes using the system calls:
 *     =>  fork() creates a new process by duplicating the calling process.
           The new process is referred to as the child process.  
           The calling process is referred to as the parent process.

 *     =>  execlp() system call belongs to the exec() family.
           The exec() family of functions replaces the current process image with a new process image.
           Prototype:  int execlp(const char *file, const char *arg, ...);

 *     =>  pid_t getpid() returns the process ID (PID) of the calling process.
 *     =>  pid_t getppid() returns the process ID of the parent of the calling process.
 *     =>  pid_t wait(int *wstatus) suspends execution of the calling thread until one of its children terminates.
 *     =>  sleep() causes the calling thread to sleep either: 
           1) Until the number of real-time seconds specified in seconds have elapsed or
           2) Until a signal arrives which is not ignored.
           Prototype: unsigned int sleep(unsigned int seconds)
 *     =>  The exit() function causes normal process termination and the lsb of status is returned to the parent.
           lsb - Least Significant Byte
           Prototype: noreturn void exit(int status);
**********************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main() {
    pid_t child_pid, my_pid, parent_pid, wid;
    int i = 10;
    child_pid = fork();
    if (child_pid < 0) {
        printf("\nFork failed, exiting!!");
        exit(0);
    }
    if (child_pid == 0) {
        // This is the child process part
        printf("\n[CHILD] This is the child process.\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[CHILD] My pid is %d\n", my_pid);
        printf("[CHILD] My parent's pid is %d\n", parent_pid);
        printf("[CHILD] i = %d\n", --i);
        printf("[CHILD] Child process going to load another program using execlp system call\n");
        execlp("/bin/pwd", "pwd", NULL);
    } else {
        // This is the parent process part
        printf("\n[PARENT] This is the parent process.\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[PARENT] My pid is %d\n", my_pid);
        printf("[PARENT] Waiting for the child to terminate.\n");
        wid = wait(NULL);
        printf("\n[PARENT] Resuming after the termination of %d\n", wid);
        printf("[PARENT] My parent's pid is %d\n", parent_pid);
        printf("[PARENT] My child's pid is %d\n", child_pid);
        printf("[PARENT] i = %d\n", ++i);
    }

    return 0;
}
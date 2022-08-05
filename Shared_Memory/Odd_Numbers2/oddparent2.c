/*********************************************************************************************************
 * Parent program to print n odd numbers using shmget and shmat system calls.
 * Prototype for shmget: int shmget(key_t key, size_t size, int shmflg);
 * shmget() returns the identifier of the shared memory, associated with the value of the argument key.
 * key_t is used for values for interprocess communication.
 * Prototype for shmat: void *shmat(int shmid, const void *shmaddr, int shmflg); 
 * shmat() attaches the shared memory segment of shmid to the address space of the calling process.
 * Prototype for shmctl: int shmctl(int shmid, int cmd, struct shmid_ds *buf);
 * shmctl() performs the control operation specified by cmd on the shared memory given by shmid.
 * Prototype for shmdt: int shmdt(const void *shmaddr);
 * shmdt() detaches the shared memory specified by shmaddr from the address space of the calling process.
*********************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/mman.h>

int main(int argc, char *argv[]) {
    int i, n;
    pid_t pid;
    const int SIZE = 4096;
    void *shmptr;
    int shmid = shmget((key_t)1122, 4096, 0666|IPC_CREAT);
    shmptr = shmat(shmid, NULL, 0666);

    if(argc > 1) {
        sscanf(argv[1], "%d", &i);
        if(i < 1) {
            printf("\nWrong input is passed:\n");
            return 0;
        }
    } else {
        printf("\nN is not passed in the command line\n");
        return 1;
    }

    pid = fork();
    if(pid == 0) {
        //This is the child process part
        execlp("./odd", "odd", argv[1], NULL);
    } else if(pid > 0) {
        wait(NULL);
        printf("\n[PARENT] Child completed\n");
        printf("\nParent printing:\n");
        printf("%s\n", (char *)shmptr);
        shmdt(shmptr); 
    } 

    return 0;
}

/*********************************************************************************************************
 * Child program to print fibonacci numbers using shmget and shmat system calls.
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
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/mman.h>

int main(int argc, char *argv[]) {
    int i, m, n, flag=0;
    void *shmptr;
    int shmid = shmget((key_t)1122, 4096, 0666);
    shmptr = shmat(shmid, NULL, 0666);

    printf("\nChild Printing:\n");
    m = atoi(argv[1]);
    n = atoi(argv[2]);
    for(i=m; i<=n; i++) {
        for(int j=2; j<=n/2; j++) {
            if(i%j == 0) {
                flag = 1;
            }     
        }

        if(flag == 0) {
        sprintf(shmptr, "%d ", i);
        printf("%d ", i);
        shmptr += strlen(shmptr);
        }

        flag = 0;
    }

    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

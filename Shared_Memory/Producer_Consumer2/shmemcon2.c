/*********************************************************************************************************
 * Consumer program to implement producer consumer problem using shmget and shmat system calls.
 * Prototype for shmget: int shmget(key_t key, size_t size, int shmflg);
 * shmget() returns the identifier of the shared memory, associated with the value of the argument key.
 * key_t is used for values for interprocess communication.
 * Prototype for shmat: void *shmat(int shmid, const void *shmaddr, int shmflg); 
 * shmat() attaches the shared memory segment of shmid to the address space of the calling process.
 * Prototype for shmctl: int shmctl(int shmid, int cmd, struct shmid_ds *buf);
 * shmctl() performs the control operation specified by cmd on the shared memory given by shmid.
 * IPC_RMID marks the segment to be destroyed.
 * Prototype for shmdt: int shmdt(const void *shmaddr);
 * shmdt() detaches the shared memory specified by shmaddr from the address space of the calling process.
**********************************************************************************************************/

//Headers to be included
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int main() {
    void *shmptr;
    char buffer[25];
    int shmid = shmget((key_t)1122, 2048, 0666);
    printf("Key of the shared memory is %d\n", shmid);
    shmptr = shmat(shmid, NULL, 0666);
    printf("The memory is attached at %p\n", shmptr);
    printf("\nThe data read from the shared memory is %s\n", (char *)shmptr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
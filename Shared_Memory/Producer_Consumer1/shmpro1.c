/*********************************************************************************************************
 * Producer program to implement producer consumer problem using shm_open and mmap system calls.
 * Prototype of shm_open: int shm_open(const char *name, int oflag, mode_t mode);
 * shm_open() creates and opens a new, or opens an existing, POSIX shared memory object.
 * Protoype of mmap: void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
 * mmap() creates a new mapping in the virtual address space of the calling process.  
 * The starting address for the new mapping is specified in addr.
 * Prototype of ftruncate:  int ftruncate(int fd, off_t length);
 * The ftruncate() functions cause the regular file named by path or referenced by fd to be truncated 
   to a size of precisely length bytes.
 * Protoype of shm_unlink: int shm_unlink(const char *name);
 * The shm_unlink() function removes the object previously created by shm_open().
*********************************************************************************************************/

//Header files to be linked
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> //POSIX Library is linked
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<sys/mman.h>
#include<sys/ipc.h>

int main() {
    void *shmptr;
    char buffer[25];
    int shmid;
    shmid = shm_open("OS", O_CREAT|O_RDWR, 0666);
    ftruncate(shmid, 2048);
    shmptr = mmap(0, 2048, PROT_WRITE, MAP_SHARED, shmid, 0);
    printf("\nKey/Id/Fd of the shared memory is %d\n", shmid);
    printf("Shared memory is attached at %p\n", shmptr);
    printf("\nEnter the string to be written into the shared memory:\n");
    read(0, buffer, 25);
    sprintf(shmptr, "%s", buffer);

    return 0;
}

/*********************************************************************************************************
 * Consumer program to implement producer consumer problem using shm_open and mmap system calls.
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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int main() {
    void *shmptr;
    int shmid = shm_open("OS", O_RDONLY, 0666);
    ftruncate(shmid, 2048);
    shmptr = mmap(0, 2048, PROT_READ, MAP_SHARED, shmid, 0);
    printf("\nShared memory is attached at %p\n", shmptr);
    printf("\nThe string entered to the shared memory is:\n");
    printf("%s\n", (char *)shmptr);
    shm_unlink("OS");

    return 0;
}
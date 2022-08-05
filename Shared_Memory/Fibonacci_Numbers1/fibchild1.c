/*********************************************************************************************************
 * Child program to print fibonacci numbers using shm_open and mmap system calls.
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
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/mman.h>

int main(int argc, char *argv[]) {
    int k=2, n1, n2, n3;
    void *shmptr;
    int shm_fd = shm_open("OS", O_CREAT|O_RDWR, 0666);
    ftruncate(shm_fd, 4096);
    shmptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    printf("\nChild Printing:\n");
    int i = atoi(argv[1]);
    n3 = n1 = 0;
    n2 = 1;
    for(k=1; k<=i; k++) {
        sprintf(shmptr, "%d ", n3);
        printf("%d ", n3);
        shmptr += strlen(shmptr);
        n1 = n2;
        n2 = n3;
        n3 = n1+n2;
    }

    return 0;
}

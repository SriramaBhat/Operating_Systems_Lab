/*********************************************************************************************************
 * Child program to print n odd numbers using shm_open and mmap system calls.
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
    int n, i=1;
    void *shmptr;
    int shmid = shm_open("OS", O_CREAT|O_RDWR, 0666);
    ftruncate(shmid, 4096);
    shmptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shmid, 0);
    printf("\nChild Printing:\n");
    n = atoi(argv[1]);
    
    while(n != 0) {
        if(i%2 != 0) {
            sprintf(shmptr, "%d ", i);
            printf("%d ", i);
            shmptr += strlen(shmptr);
            n--;
        }
        i++;
    }

    return 0;
}

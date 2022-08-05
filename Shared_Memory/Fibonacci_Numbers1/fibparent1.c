/*********************************************************************************************************
 * Parent program to print fibonacci numbers using shm_open and mmap system calls.
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
    int i, k, n1, n2, n3;
    const int SIZE = 4096;
    pid_t pid;
    int shm_fd;
    void *shmptr;

    if (argc > 1) {
        sscanf(argv[1], "%d", &i);
        if(i<1) {
            printf("\nWrong input given!!\n");
            return 0;
        }
    } else {
        printf("\nN is not passed in the command line!!\n");
        exit(0);
    }

    pid = fork();
    if(pid == 0) {
        //This is the child part
        execlp("./fib", "fib", argv[1], NULL);
    } else if (pid > 0) {
        wait(NULL);
        printf("\n[PARENT] Child process completed\n");
        shm_fd = shm_open("OS", O_RDONLY, 0666);
        shmptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        printf("\nParent printing:\n");
        printf("%s\n", (char *)shmptr);
        shm_unlink("OS");
    }

    return 0;
}

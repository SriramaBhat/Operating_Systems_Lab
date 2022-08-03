/************************************************************************************************************************
 * Program to dmeonstrate the file I/O system calls for reading from a file and write into new file.
 * The following system calls are used:
 *   =>   read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.
          Prototype: ssize_t read(int fd, void *buf, size_t count);
          File descriptor for the stdin steam is 0
 *   =>   write() writes up to count bytes from the buffer starting at buf to the file descriptor fd.
          Prototype: ssize_t write(int fd, const void *buf, size_t count);
          File descriptor for the stdout stream is 1
 * ssize_t is used for a count of bytes or an error indication.
 *   =>    The open() system call opens the file specified by pathname.
           Prototype:  int open(const char *pathname, int flags);
           Some of the most used flags are:
               O_RDONLY: Open for reading only.
               O_WRONLY: Open for writing only.
               O_RDWR: Open for reading and writing.
               O_CREAT: If the file does not exist, the file shall be created, else it is just opened.
               O_EXCL: Prevents creation if file already exists
*************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#define BUFFER_SIZE 500

int main() {
    int fd1, fd2, n;
    char buffer[BUFFER_SIZE];
    fd1 = open("sample.txt", O_RDONLY);
    fd2 = open("copy.txt", O_CREAT|O_WRONLY, 0666);
    printf("\nFile descriptor for sample.txt is %d and for copy.txt is %d\n", fd1, fd2);
    if (fd1 == -1 || fd2 == -1) {
        printf("\nFailed to open file\n");
        exit(0);
    }

    n = read(fd1, buffer, BUFFER_SIZE);
    write(fd2, buffer, n);
    printf("\nFile has been created and copied successfully\n");
    return 0;
}
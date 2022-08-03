/******************************************************************************************************************
 * Program to demonstrate the I/O system calls for console.
 * The following system calls are used:
 *   =>   read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.
          Prototype: ssize_t read(int fd, void *buf, size_t count);
          File descriptor for the stdin steam is 0
 *   =>   write() writes up to count bytes from the buffer starting at buf to the file descriptor fd.
          Prototype: ssize_t write(int fd, const void *buf, size_t count);
          File descriptor for the stdout stream is 1
 * ssize_t is used for a count of bytes or an error indication.
*******************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define BUFFER_SIZE 30

int main() {
    char buffer[BUFFER_SIZE];
    int n;
    printf("\nEnter the string:\n");
    n = read(0, buffer, BUFFER_SIZE);
    printf("\nThe number of characters read are %d\n", n);
    write(1, buffer, n);
    return 0;
}
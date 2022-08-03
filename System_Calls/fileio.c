/************************************************************************************************************************
 * Program to dmeonstrate the file I/O system calls for console and file
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
 *   =>     lseek() repositions the file offset of the file descriptor fd to the argument offset.
            Prototype: off_t lseek(int fd, off_t offset, int whence);
            The parameter whence can be set to the following values:
                 SEEK_SET: The file offset is set to offset bytes.
                 SEEK_CUR: The file offset is set to its current location plus offset bytes.
                 SEEK_END: The file offset is set to the size of the file plus offset bytes.                 
 * off_t is used for file sizes.
************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#define BUFFER_SIZE 50

int main() {
    int fd, n;
    char buffer[BUFFER_SIZE];
    fd = open("sample.txt", O_RDWR);
    printf("\nThe file descriptor is %d\n", fd);
    if (fd == -1) {
        printf("\nFailed to open the file.\n");
        exit(0);
    }

    printf("\nReading first 10 characters from the file:\n");
    n = read(fd, buffer, 10);
    write(1, buffer, n);
    printf("\nSkipping 5 characters from the current position in the file:\n");
    lseek(fd, 5, SEEK_CUR);
    n = read(fd, buffer, 10);
    write(1, buffer, n);
    printf("\nGoing to 7 characters before current position in file:\n");
    lseek(fd, -7, SEEK_CUR);
    n = read(fd, buffer, 10);
    write(1, buffer, n);

    printf("\nGoing to 5th last character in the file:\n");
    lseek(fd, -5, SEEK_END);
    n = read(fd, buffer, 7);
    write(1, buffer, 5);
    printf("\nGoing to the third character in the file:\n");
    lseek(fd, 3, SEEK_SET);
    n = read(fd, buffer, 5);
    write(1, buffer, n);
    printf("\n");

    return 0;
}
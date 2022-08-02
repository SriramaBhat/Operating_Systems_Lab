/**************************************************************************************************************
 * Program to stimulate the ls command of Linux operating system.
 * The ls command lists all the files present in the given directory.
 * The <dirent.h> header defines the following data type through typedef:
 *     DIR is a type representing the directory stream.
 *     It also defines a structure called dirent, which has the members:
 *           => ino_t d_ino //File serial name.
 *           => char d_name //Name of the directory.
 * The type ino_t is defined in the header <sys/types.h>, and is used for file serial numbers.
 * The . present in the output represents the current directory.
 * The .. present in the output represents the parent directory.
**************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>

//The directory name is to be passed as a command line argument.
void main(int argc, char *argv[]) {
    DIR *dp;
    struct dirent *dirp;
    if(argc < 2) {
        printf("\nThe directory name is not being passed.\n");
        exit(1);
    }

    if((dp = opendir(argv[1])) == NULL) {
        printf("\nDirectory does not exist, and therefore cannot be opened.\n");
        exit(1);
    }

    while((dirp = readdir(dp)) != NULL) {
        printf("%s\n", dirp->d_name);
    }
    closedir(dp);
}
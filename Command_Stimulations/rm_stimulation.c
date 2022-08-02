/*************************************************************************************************
 * Program to stimulate the rm command of the linux operating system.
 * The rm command is used for deleting a file present in the current directory.
 * To stimulate this, the remove() function is used.
 * The remove function checks the file name, and if existing, removes the file.
*************************************************************************************************/

#include<stdio.h>
void main() {
    char file_name[25];
    printf("\nEnter the source file\n");
    scanf("%s", file_name);
    if(remove(file_name) == 0)
        printf("\nFile successfully removed\n");
    else
        printf("\nFile cannot be removed\n");
}
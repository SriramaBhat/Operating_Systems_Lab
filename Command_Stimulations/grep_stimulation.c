/***************************************************************************************************************************
 * Program to stimulate the grep command of linux operating system.
 * The grep command finds the required pattern in the given file, and prints the lines with the pattern to console.
 * It is stimulated using FILE which is an object type suitable for storing information for a file stream.
 * fgets() reads a line from the specified stream and stores it into the string.
 * It stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached.
 * Prototype: char *fgets(char *str, int n, FILE *stream)
 * int feof(FILE *stream) tests the end-of-file indicator for the given stream.
 * strstr() function finds the first occurrence of the given substring in the given string.
 * Prototype: char *strstr(const char *haystack, const char *needle)
***************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main() {
    char file_name[25], pattern[10], temp[200];
    FILE *fp;
    printf("\nEnter the file name:\n");
    scanf("%s", file_name);
    printf("\nEnter the pattern:\n");
    scanf("%s", pattern);
    fp = fopen(file_name, "r");
    while (!feof(fp)) {
        fgets(temp, 100, fp);
        if(strstr(temp, pattern))
            printf("%s", temp);
    }
    fclose(fp);
}

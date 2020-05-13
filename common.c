#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <time.h>
#include <math.h>
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  The math.h library must be linked upon compilation
 *  gcc partA.c -o partA -lm
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void create_test_file(int, char *, FILE *);

int main(void) {

    int i = 0, limit = 7;
    clock_t start, end;
    char *cPtr = NULL;

    // Save the output from the experiment into a csv file.
    FILE *csvPtr;
    csvPtr = fopen("partA.csv", "w");
    fprintf(csvPtr, "size,time\n");

    // The C math.h pow(2,i) function doubles the file size in each step by
    // passing i into the create_test_file(i) function as a base 2 exponent.
    // The loop stops at 7 because 2^7 = 128.
    for (;i <= limit; i++) {

        // create_test_file(int) creates two files on the fly from 1MB ... 128MB with the
        // size of the files depending on what position in the loop, i, the program is at.
        create_test_file(i, cPtr, csvPtr);

        int fd1 = open("file_A", O_RDWR);
        int fd2 = open("file_B", O_RDWR);

        // System clock, end - start, measures read() and write() times.
        start = clock();
        char c;
        while (read(fd1, &c, 1) == 1) {
            write(fd2, &c, 1);
        }
        end = clock();
        double elapsedTime = ((double) (end - start)) / CLOCKS_PER_SEC;

        // Accuracy of the system clock goes to three decimal points.
        printf("(Read/write time) %0.3f seconds\n", elapsedTime);

        // Save the read/write time into the csv file.
        fprintf(csvPtr, "%0.3f\n", elapsedTime);

        close(fd1);
        close(fd2);
    }

    fclose(csvPtr);
    remove("file_A");
    remove("file_B");
    free(cPtr);

    return 0;
}

// This function takes in the number of times you should multiply
// a megabyte by to get the total size of two dynamically allocated
// files: file_A and file_B. These files are local and get
// deleted at the end of the program.
void create_test_file(int i, char *cPtr, FILE *csv) {

    int size = (int) (1024 * 1024 * pow(2, i));
    FILE *fPtr;

    cPtr = malloc(sizeof(char*) * size);

    // Save the file size into the csv file.
    printf("(File size) %d bytes ", size);
    fprintf(csv, "%d,", size);

    fPtr = fopen("file_A", "w");
    memset(cPtr, 'A', size);
    fputs((const char *) cPtr, fPtr);
    fclose(fPtr);

    fPtr = fopen("file_B", "w");
    memset(cPtr, 'B', size);
    fputs((const char *) cPtr, fPtr);
    fclose(fPtr);
}
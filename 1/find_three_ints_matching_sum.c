#include <stdio.h>
#include <string.h>
#include <errno.h>

#define TARGET_SUM 2020

// TODO: Create helper to read input from file of arbitrary length

// TODO: More efficient solution may involve sorting arr


/*
    Find subset of size k of arr inputArr that sums to TARGET_SUM
    Result: product of each member of the subset
*/
int combinations_sum(int *inputArr, int length){
    printf("length: %d\n", length);
    for (int i=0; i<length-2; i++){
        for (int j=i+1; j<length-1; j++){
            for (int k=j+1; k<length; k++){
                if((inputArr[i] + inputArr[j] + inputArr[k]) == TARGET_SUM){
                    int result = inputArr[i]*inputArr[j]*inputArr[k];
                    printf("%d %d %d\n", i, j, k);
                    printf("Result subset: %d %d %d\n", inputArr[i], inputArr[j], inputArr[k]);
                    return result;
                }
            }
        }
    }
    return -1;
}


int main(int argc, char *argv[]) {
    FILE *file;
    // argv[1] is filename
    file = fopen(argv[1], "rb");
    if (!file) {
        // alternatively, just `perror(argv[1])`
        fprintf(stderr, "cannot open %s: %s\n", argv[1], strerror(errno));
        return 1;
    }  

    // Read from file into array of ints
    int inputArr[200];
    int i = 0;
    while (!feof (file)){
        fscanf(file, "%d", &(inputArr[i]));
        i++;
    }
    fclose(file);

    printf("Size of arr: %d\n", (int) sizeof(inputArr));  // size in bytes
    printf("Length of arr: %d\n", (int) (sizeof(inputArr) / sizeof(inputArr[0])));

    int length = sizeof(inputArr) / sizeof(inputArr[0]);

    int result = combinations_sum(inputArr, length);

    if (result < 0){
        printf("Error: pair of inputs summing to 2020 not found\n");
        return 1;
    }

    printf("Result: %d\n", result);
    return 0;

}
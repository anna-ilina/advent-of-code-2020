#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_PASSWORD_LENGTH 50

/*
    Determine whether password string matches char `letter`
    at index1 xor index2. (Note: the indexes are 1-indexed).
    Result: 1 if password meets requirements, otherwise 0
*/
int password_is_valid(int index1, int index2, char letter, char *password){
	return password[index1-1] == letter ^ password[index2-1] == letter;
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

    // Read from file, one row at a time
    int index1, index2;
    char letter;
    char password[MAX_PASSWORD_LENGTH];
    int countMatchingPasswords = 0;
    while (!feof (file)){
        fscanf(file, "%d-%d %c: %s", &index1, &index2, &letter, &password[0]);
        // printf("\n%d %d %c %s\n", index1, maxCount, letter, password);
        if (password_is_valid(index1, index2, letter, password)){
            countMatchingPasswords++;
        }
    }
    fclose(file);

    printf("Result: %d\n", countMatchingPasswords);
    return 0;
}
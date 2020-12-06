#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_PASSWORD_LENGTH 50

/*
    Determine whether password string contains between minCount and maxCount
    instances of char 'letter'.
    Result: 1 if password meets requirements, otherwise 0
*/
int password_is_valid(int minCount, int maxCount, char letter, char *password){
    int count=0;
    int i=0;
    // printf("Checking %c for password: %s (%lu)\n", letter, password, strlen(password));
    while(i < strlen(password)){
        // printf("Comparing %c : %c\n", password[i], letter);
        if (password[i] == letter){
            // printf("matching letter found\n");
            count++;
            if (count > maxCount){
                return 0; // TODO: Confirm this returns from fn
            }
        }
        i++;
    }
    return count >= minCount && count <= maxCount;
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
    int minCount, maxCount;
    char letter;
    char password[MAX_PASSWORD_LENGTH];
    int countMatchingPasswords = 0;
    while (!feof (file)){
        fscanf(file, "%d-%d %c: %s", &minCount, &maxCount, &letter, &password[0]);
        // printf("\n%d %d %c %s\n", minCount, maxCount, letter, password);
        if (password_is_valid(minCount, maxCount, letter, password)){
            countMatchingPasswords++;
        }
    }
    fclose(file);

    printf("Result: %d\n", countMatchingPasswords);
    return 0;
}
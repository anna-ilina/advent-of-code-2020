#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <errno.h>

#define KEY_SIZE 3
#define MAX_INPUT_SIZE 50
#define NUM_REQUIRED_KEYS 7


int endOfPassword(FILE *stream) {
    int c1, c2, c3;

    c1 = fgetc(stream);
    c2 = fgetc(stream);
    c3 = fgetc(stream);
    ungetc(c3, stream);
    ungetc(c2, stream);
    ungetc(c1, stream);

    return (c1 == EOF || c1 == '\r' && c2 == '\n' && c3 == '\r');
}


int validateIntString(char *string, int minInclusive, int maxInclusive) {
    // Assume year strings consist of four digits
    char *end;
    int parsedValue = strtol(string, &end, 10);
    if (parsedValue >= minInclusive && parsedValue <=maxInclusive) {
        return 1;
    }
    return 0;
}


int isRequiredAndValidEntry(char *key, char *value) {
    // char requiredKeys[NUM_REQUIRED_KEYS][KEY_SIZE+1] = {
    //     "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"
    // };

    int len = strlen(value);

    if (strcmp(key, "byr") == 0){
        // validate year string
        if (validateIntString(value, 1920, 2002)) {
            return 1;
        }
    } else if (strcmp(key, "iyr") == 0){
        // validate year string
        if (validateIntString(value, 2010, 2020)) {
            return 1;
        }
    } else if (strcmp(key, "eyr") == 0){
        // validate year string
        if (validateIntString(value, 2020, 2030)) {
            return 1;
        }
    } else if (strcmp(key, "hgt") == 0){
        // Validate that 150cm <= value <= 193cm
        // or 59in <= value <= 76in
        if (value[len-2] == 'c' && value[len-1] == 'm'){
            if (validateIntString(value, 150, 193)){
                return 1;
            }
        } else if (value[len-2] == 'i' && value[len-1] == 'n'){
            if (validateIntString(value, 59, 76)){
                return 1;
            }
        }
    } else if (strcmp(key, "hcl") == 0){
        if (value[0] == '#' && len == 7) {
            // Validate that '#' is followed by exactly 6 chars 0-9 or a-f
            for (int i=1; i<7; i++){
                if (!(value[i] >= '0' && value[i] <= '9' || value[i] >= 'a' && value[i] <= 'f')) {
                    return 0;
                }
            }
            return 1;
        }
    } else if (strcmp(key, "ecl") == 0){
        // Validate that value is one of: amb blu brn gry grn hzl oth
        if (
            strcmp(value, "amb") == 0 ||
            strcmp(value, "blu") == 0 ||
            strcmp(value, "brn") == 0 ||
            strcmp(value, "gry") == 0 ||
            strcmp(value, "grn") == 0 ||
            strcmp(value, "hzl") == 0 ||
            strcmp(value, "oth") == 0
        ) {
            return 1;
        }
    } else if (strcmp(key, "pid") == 0){
        // Validate that value is a 9 digit number, including leading zeroes
        if (len == 9) {
            for (int i=0; i<9; i++){
                if (!(value[i] >= '0' && value[i] <= '9')) {
                    return 0;
                }
            }
            return 1;
        }
    }

    // ignore key "cid" since it's optional

    return 0;
}


int main(int argc, char *argv[]) {
    FILE *file;
    // argv[1] is filename
    file = fopen(argv[1], "r");
    if (!file) {
        // alternatively, just `perror(argv[1])`
        fprintf(stderr, "cannot open %s: %s\n", argv[1], strerror(errno));
        return 1;
    }

    // Read passports from file
    char key[KEY_SIZE+1];
    char value[MAX_INPUT_SIZE];
    int numValidPassports = 0;
    int numMatchingKeys = 0;
    while (!feof (file)) {
        fscanf(file, "%3s:%s", &key[0], &value[0]);

        printf("Scanned password KEY: %s  VALUE: %s\n", key, value);

        if (isRequiredAndValidEntry(key, value)){
            numMatchingKeys++;
        }

        // Detect blank line or EOF
        if (endOfPassword(file)) {
            printf("END OF PASSWORD (%d), %s\n\n", numMatchingKeys, numMatchingKeys >= 7 ? "VALID" : "INVALID");

            // End of password: check if password is valid and reset numMatchingKeys
            if (numMatchingKeys >= 7) {
                numValidPassports++;
            }
            numMatchingKeys = 0;
        }

    }
    fclose(file);

    printf("Result: %d\n", numValidPassports);
    return 0;
}
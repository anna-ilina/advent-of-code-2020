#include <stdio.h>
#include <string.h>
#include <errno.h>

#define KEY_SIZE 3
#define MAX_INPUT_SIZE 50
#define NUM_REQUIRED_KEYS 7

char fpeek(FILE *stream) {
    int c;

    c = fgetc(stream);
    ungetc(c, stream);

    return c;
}

char fpeekTwo(FILE *stream) {
    int c1, c2;

    c1 = fgetc(stream);
    c2 = fgetc(stream);
    ungetc(c2, stream);
    ungetc(c1, stream);

    return c2;
}


int endOfPassword(FILE *stream) {
    int c1, c2, c3;

    c1 = fgetc(stream);
    c2 = fgetc(stream);
    c3 = fgetc(stream);
    ungetc(c3, stream);
    ungetc(c2, stream);
    ungetc(c1, stream);

    // printf(
    //     "Peek: %d, carriageReturn: %d, newLine: %d, EOF: %d\n",
    //     c1, c1 == '\r', c1 == '\n', c1 == EOF
    // );
    // printf(
    //     "Peek2: %d, carriageReturn: %d, newLine: %d,EOF: %d\n",
    //     c2, c2 == '\r', c1 == '\n', c2 == EOF
    // );
    // printf(
    //     "Peek3: %d, carriageReturn: %d, newLine: %d,EOF: %d\n",
    //     c3, c3 == '\r', c3 == '\n', c3 == EOF
    // );

    return (c1 == EOF || c1 == '\r' && c2 == '\n' && c3 == '\r');
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
    char entry[MAX_INPUT_SIZE];

    char requiredKeys[NUM_REQUIRED_KEYS][KEY_SIZE+1] = {
        "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"
    };

    int numValidPassports = 0;
    int numMatchingKeys = 0;
    while (!feof (file)) {
       fscanf(file, "%s", &entry[0]);

        // printf("Scanned password entry=%s\n", entry);

        int i=0;
        while (i < NUM_REQUIRED_KEYS) {
            if (memcmp(entry, requiredKeys[i], KEY_SIZE) == 0) {
                // printf("\tmatching key (%s)\n", requiredKeys[i]);
                numMatchingKeys++;
            }
            i++;
        }

        // char nextChar = fpeek(file);
        // char nextChar2 = fpeekTwo(file);
        // printf("Peek: %d, isEmptyString: %d, isEndOfFile: %d\n", nextChar, nextChar == '\r', nextChar == EOF);
        // printf("Peek2: %d, isEmptyString: %d, isEndOfFile: %d\n", nextChar2, nextChar2 == '\r', nextChar2 == EOF);

        // Detect blank line or EOF
        if (endOfPassword(file)) {
            printf("END OF PASSWORD (%d)\n\n", numMatchingKeys);

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
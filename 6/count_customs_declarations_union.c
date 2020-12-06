#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <errno.h>

#define NUM_QUESTIONS 26


int blankLineNext(FILE *stream) {
    int c1, c2, c3;

    c1 = fgetc(stream);
    c2 = fgetc(stream);
    c3 = fgetc(stream);
    ungetc(c3, stream);
    ungetc(c2, stream);
    ungetc(c1, stream);

    return (c1 == EOF || c1 == '\r' && c2 == '\n' && c3 == '\r');
}


void markAnsweredQuestions(char *input, char *questions){
    int len = strlen(input);
    for (int i=0; i<len; i++){
        questions[input[i] - 'a'] = 'X';
    }
}

void resetQuestions(char *questions){
    for (int i=0; i < NUM_QUESTIONS; i++){
        questions[i] = 'O';
    }
    questions[NUM_QUESTIONS] = '\0';
}

int countAnsweredQuestions(char *questions){
    int count = 0;
    for (int i=0; i < NUM_QUESTIONS; i++){
        if (questions[i] == 'X') {
            count++;
        }
    }
    return count;
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

    // Create array of chars to keep track of answered questions
    char questions[NUM_QUESTIONS + 1];
    resetQuestions(questions);

    // Read passports from file
    int result = 0;
    char inputLine[NUM_QUESTIONS+1];
    while (!feof (file)) {
        fscanf(file, "%s", &inputLine[0]);

        markAnsweredQuestions(inputLine, questions);

        if (blankLineNext(file)){
            int numAnsweredQuestions = countAnsweredQuestions(questions);
            printf("End of group reached, answered Q's: %s (%d)\n", questions, numAnsweredQuestions);
            result += numAnsweredQuestions;
            resetQuestions(questions);
        }

    }
    fclose(file);

    printf("Result: %d\n", result);
    return 0;
}
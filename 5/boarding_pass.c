#include <stdio.h>
#include <string.h>
#include <errno.h>

#define INPUT_LINE_SIZE 10


// Iterative solution would be faster for large input
// (here input strings are 10 chars)

// Iterate recursively through `seat` while lowerChar/upperChar are matched.
// We are searching for int value within range defined by [min, max)
// On input lowerChar: search lower half of input range
// On input upperChar: search upper half of input range
int findSeat(char *seat, int index, int min, int max, char lowerChar, char upperChar) {
    // printf("\t\tmin: %d, max: %d, char: %c\n", min, max, seat[index]);
    if (seat[index] == lowerChar) {
        return findSeat(seat, index+1, min, min + (max-min)/2, lowerChar, upperChar);
    } else if (seat[index] == upperChar) {
        return findSeat(seat, index+1, min + (max-min)/2, max, lowerChar, upperChar);
    } else {
        // Have reached end of current section
        return min;
    }
}


int getSeatID(char *seat) {
    int row = findSeat(seat, 0, 0, 128, 'F', 'B');
    int col = findSeat(seat, 7, 0, 8, 'L', 'R');
    printf("\trow: %d, col: %d\n", row, col);
    return 8*row + col;
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
    char seat[INPUT_LINE_SIZE+1];
    int maxSeatID = 0;
    while (!feof (file)) {
        fscanf(file, "%s", &seat[0]);

        int seatID = getSeatID(seat);

        printf("Scanned seat: %s (%d)\n", seat, seatID);

        if (seatID > maxSeatID) {
            maxSeatID = seatID;
        }

    }
    fclose(file);

    printf("Result: %d\n", maxSeatID);
    return 0;
}
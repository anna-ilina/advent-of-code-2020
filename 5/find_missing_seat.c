#include <stdio.h>
#include <string.h>
#include <errno.h>

#define INPUT_LINE_SIZE 10
#define NUM_ROWS 128
#define NUM_COLS 8
#define NUM_SEATS NUM_ROWS * NUM_COLS


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


// a seat is represented by a 10 char string
int getSeatID(char *seat) {
    // row is represented by first 7 chars of seat string
    int row = findSeat(seat, 0, 0, NUM_ROWS, 'F', 'B');
    // col is represented by last 3 chars of seat string
    int col = findSeat(seat, 7, 0, NUM_COLS, 'L', 'R');
    printf("\trow: %d, col: %d\n", row, col);
    return NUM_COLS*row + col;
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

    // int minSeatID = NUM_COLS*0 + 0; // min seat has row 0 and col 0
    // int maxSeatID = NUM_COLS*(NUM_ROWS-1) + NUM_COLS-1 // max seat has row 127 and col 7

    // Create array of chars to keep track of which seats are occupied
    char occupiedSeats[NUM_SEATS + 1];
    for (int i=0; i < NUM_SEATS; i++){
        occupiedSeats[i] = 'O';
    }
    occupiedSeats[NUM_SEATS] = '\0';

    // Read passports from file
    char seat[INPUT_LINE_SIZE+1];
    while (!feof (file)) {
        fscanf(file, "%s", &seat[0]);

        // int row = findSeat(seat, 0, 0, 128, 'F', 'B');
        // int col = findSeat(seat, 7, 0, 8, 'L', 'R');
        // int seatID = 8*row + col;
        // printf("Scanned seat: %s (%d)\t row: %d\tcol: %d\n", seat, seatID, row, col);

        int seatID = getSeatID(seat);
        occupiedSeats[seatID] = 'X';
        printf("Scanned seat: %s (%d)\n", seat, seatID);
    }
    fclose(file);

    printf("occupied seats: %s\n", occupiedSeats);

    // Find missing seat (the seats with IDs +1 and -1 from it will be occupied)
    for (int i=1; i<NUM_SEATS-1; i++){
        if (occupiedSeats[i] == 'O' && occupiedSeats[i-1] == 'X' && occupiedSeats[i+1] == 'X'){
            printf("Result: %d\n", i);
            return 0;
        }
    }

    printf("No available seat found\n");
    return 1;
}
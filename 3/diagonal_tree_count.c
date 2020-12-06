#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_INPUT_WIDTH 50
#define TREE_CHAR '#'


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
    int row = 0;
    int col = 0;
    char rowString[MAX_INPUT_WIDTH];
    int rowLength;
    int treeCount = 0;
    while (!feof (file)) {
        fscanf(file, "%s", &rowString[0]);

        if (row == 0) {
            // All rows have same length
            rowLength = strlen(rowString);
        } else {
            col += 3;
            col = col % rowLength;
            if (rowString[col] == TREE_CHAR) {
                treeCount++;
            }
            // printf("On row %d col %d, tree count is %d\n", row, col, treeCount);
        }
        row++;
    }
    fclose(file);

    printf("Result: %d\n", treeCount);
    return 0;
}
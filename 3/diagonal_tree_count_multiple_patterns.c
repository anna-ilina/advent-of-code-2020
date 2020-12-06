#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_INPUT_WIDTH 50
#define MAX_INPUT_LENGTH 350
#define TREE_CHAR '#'
#define NUM_PATHS 5


// Count trees encountered if on each move you traverse the grid
//  right `colStep` columns and down `rowStep` rows.
// (The grid spans right infinitely)
int countTrees(char grid[MAX_INPUT_LENGTH][MAX_INPUT_WIDTH+1], int numRows, int numCols, int colStep, int rowStep){

    int treeCount = 0;
    int row=0;
    int col=0;
    while (row < numRows){
        row += rowStep;
        col += colStep;
        col = col % numCols;
        if (grid[row][col] == TREE_CHAR) {
            treeCount++;
        }
    }
    return treeCount;

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

    // Read grid from file
    char grid[MAX_INPUT_LENGTH][MAX_INPUT_WIDTH+1];
    int rowCount = 0;
    while (!feof (file)) {
        fscanf(file, "%s", &grid[rowCount][0]);
        rowCount++;
    }
    fclose(file);
    int colCount = strlen(grid[0]);

    // 5 paths to consider
    int pathConfigs[NUM_PATHS][2] = {
        {1, 1},
        {3, 1},
        {5, 1},
        {7, 1},
        {1, 2}
    };

    long product = 1;
    for (int i=0; i<NUM_PATHS; i++){
        int colStep = pathConfigs[i][0];
        int rowStep = pathConfigs[i][1];

        int numTrees = countTrees(grid, rowCount, colCount, colStep, rowStep);

        printf(
            "Right %d down %d\tTree count: %d\n",
            colStep, rowStep, numTrees
        );

        product *= numTrees;
    }

    printf("Result: %ld\n", product);
    return 0;
}
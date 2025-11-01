#include <stdio.h>
#include <stdlib.h>
#include "histogram.h"

int main()
{
    int numBeads;
    int numBins;

    printf("Enter number of beads: \n");
    scanf("%d", &numBeads);

    printf("Enter number of bins: \n");
    scanf("%d", &numBins);

    // Allocate memory for bins (from user input), should init with 0
    int *board = (int *)calloc(numBins, sizeof(int));

    if (board == NULL)
    {
        printf("Allocation failed!");
        exit(0);
    }

    // Simulate board
    // Example: If there are 4 bins, then there will be 1 + 2 + 3 pegs (3 levels)
    // For the case n bins, there will be 1 + 2 + ... + n - 1 pegs (n - 1 levels)
    //          .
    //        .   .
    //      .   .   .
    //  |   |   |   |   |
    //    1   2   3   4
    // This means, if we start with 1/2 number of bins, then for each level:
    //  + .5 if bead falls right
    //  - .5 if bead falls left
    //  Taking the floor of the resulting number gives us the index of the bin the bead falls into

    for (int i = 0; i < numBeads; i++)
    {
        float index = numBins / 2;
        for (int level = 0; level < numBins - 1; level++)
        {
            // if bead falls left, subtract .5 otherwise add .5
            (rand() % 2) ? (index += 0.5f) : (index -= 0.5f);
        }

        int finalIndex = (int)index; // Takes "floor" of index, but also allows us to use to index array.
        board[finalIndex]++; // add bead to respective bin
    }
    
    // Print out values of bins
    for (int i = 0; i < numBins; i++)
        printf("%d\t", board[i]);

    //
    char** histogram = create_histogram(board, numBins, numBeads);
    display_histogram(histogram, numBins);

    return 0;
}
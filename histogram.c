#include "histogram.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HIST_HEIGHT 10

char** create_histogram(int *data, int columns, int total)
{
    // Create the histogram in memory
    char** histogram = calloc(columns, sizeof(char*));
    if (histogram == NULL) { printf("Failed to allocate histogram!"); exit(0); }

    for (int i = 0; i < columns; i++)
    {
        //histogram[i] = (char*) calloc(HIST_HEIGHT, sizeof(char));
        histogram[i] = malloc(HIST_HEIGHT * sizeof(char));
        if (histogram[i] == NULL) { printf("Failed to allocate histogram bins!"); exit(0); }
        memset(histogram[i], 'x', HIST_HEIGHT);
    }

    // Populate with data, each bin will be a percentage represented with bars

    return histogram;
}

void display_histogram(char** histogram, int columns)
{
    printf("\nPRINTING HISTOGRAM \n");
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < HIST_HEIGHT; j++)
        {
            printf("%c\t", histogram[i][j]);
        }
        printf("\n");
    }
}

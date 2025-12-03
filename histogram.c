#include "histogram.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HIST_HEIGHT 10

char** create_histogram(int *data, int columns)
{
	// Find max value in data, use for scaling histogram later
	int max = 0;
	for (int i = 0; i < columns; i++)
		if (data[i] > max)
        		max = data[i];

	// Create the histogram in memory
	char** histogram = calloc(columns, sizeof(char*));
	if (histogram == NULL) { printf("Failed to allocate histogram!"); exit(0); }

	for (int i = 0; i < columns; i++)
	{
		histogram[i] = (char*) calloc(HIST_HEIGHT, sizeof(char));
		if (histogram[i] == NULL) { printf("Failed to allocate histogram bins!"); exit(0); }

        	// Data should have same length!! if not you're doing something wrong!!
		float percentage = (float)data[i] / max;
		int barHeight = (int)HIST_HEIGHT * percentage;
		for (int j = 0; j < barHeight; j++)
			histogram[i][j] = 'x';
	}
	return histogram;
}

void display_histogram(char** histogram, int columns)
{
	printf("\n");
	for (int i = HIST_HEIGHT - 1; i > 0; i--)
	{
        	for (int j = 0; j < columns; j++)
		{
			printf("%c\t", histogram[j][i]);
		}
		printf("\n");
	}
}

void free_histogram(char** histogram, int columns)
{
    for (int i = 0; i < columns; i++)
        free(histogram[i]);

    free(histogram);
}

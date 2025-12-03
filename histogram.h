#ifndef HISTOGRAM_H
#define HISTOGRAM_H

// Takes in 1d array and outputs histogram as 2d array.
char** create_histogram(int *data, int columns);

// Takes in 2d array and prints out.
void display_histogram(char** histogram, int columns);

// Frees up the memory allocated by histogram
void free_histogram(char** histogram, int columns);

#endif

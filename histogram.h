#ifndef HISTOGRAM_H
#define HISTOGRAM_H

// Takes in 1d array and total population to create 2d array bar graph.
char** create_histogram(int *data, int columns, int total);

// Takes in 2d array and prints out.
void display_histogram(char** histogram, int columns);

#endif
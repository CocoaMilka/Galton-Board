#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#include "histogram.h"

int main(int argc, char* argv[])
{
	// MPI init stuffs :P
	int my_rank, p, source, dest, tag=0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	MPI_Status status;

	// Master process query input params, then divide and launch sub processes
	if (my_rank == 0)
	{
		// Read and store user input
		int numBeads;
		int numBins;
		printf("Enter number of beads: \n"); scanf("%d", &numBeads);
		printf("Enter number of bins: \n"); scanf("%d", &numBins);
	
		int divBeads = numBeads / (p - 1); // Master process is not participating
		int remainderBeads = numBeads % (p - 1);
		printf("Total beads: %d \nBeads per process: %d \nRemainder beads: %d \n", numBeads, divBeads, remainderBeads); 
		
		// TODO: Account for remainder beads, loop through each processor and add 1 until no more remainder	

		// Equally distribute beads across available processors
		for (int i = 1; i < p; i++)
		{
			MPI_Send(&divBeads, 1, MPI_INT, i, 1, MPI_COMM_WORLD);			
			MPI_Send(&numBins, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
		}
		
		int *board = (int *)calloc(numBins, sizeof(int));
		int *tmp_board = (int *)calloc(numBins, sizeof(int));
		
		// Recieve results and combine into single histogram
		for (int i = 1; i < p; i++)
		{
			MPI_Recv(tmp_board, numBins, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
		
			//Copy results into final board
			for (int j = 0; j < numBins; j++)
				board[j] += tmp_board[j];
		}

		// Print out values of bins
		printf("Rank: %d \n", my_rank);
		for (int i = 0; i < numBins; i++)
			  printf("%d\t", board[i]);

		free(board);
		free(tmp_board);
	} 
	else // Sub processors to simulate boards with their portion of beads and return
	{ 
		int myBeads, numBins = 0;
		
		MPI_Recv(&myBeads, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&numBins, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);		

		// Allocate memory for bins (from user input), should init with 0
		int *board = (int *)calloc(numBins, sizeof(int));
		if (board == NULL) { printf("Allocation failed!"); exit(0); }

		// Simulate board
		// Example: If there are 4 bins, then there will be 1 + 2 + 3 pegs (3 levels)
		// For the case n bins, there will be 1 + 2 + ... + n - 1 pegs (n - 1 levels)
		//			.
		//		    .	    .
		//		.	.	.
		//	|	|	|	|	|
		//	    1	    2	    3	    4
		// This means, if we start with 1/2 number of bins, then for each level:
		//	+ .5 if bead falls right
		//	- .5 if bead falls left
		//	Taking the floor of the resulting number gives us the index of the bin the bead falls into

		srand(time(NULL));
		for (int i = 0; i < myBeads; i++)
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
		//printf("Rank: %d \n", my_rank);
		//for (int i = 0; i < numBins; i++)
		//	  printf("%d\t", board[i]);

		//char** histogram = create_histogram(board, numBins);
		//display_histogram(histogram, numBins);
		
		// Send result to master process
		MPI_Send(board, numBins, MPI_INT, 0, 1, MPI_COMM_WORLD);

		// Cleanup! 
		free(board);
		//free_histogram(histogram, numBins);
	}

	MPI_Finalize();
}

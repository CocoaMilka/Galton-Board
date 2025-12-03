CC=mpicc
BINARIES=galtonboard_parallel galtonboard_parallel_debug
OBJS=main.o histogram.o

all: galtonboard_parallel

galtonboard_parallel: $(OBJS)
	$(CC) -o galtonboard_parallel $(OBJS)

galtonboard_parallel_debug: $(OBJS)
	$(CC) -Wall -o galtonboard_parallel_debug $(OBJS)

main.o: main.c 
	$(CC) -c main.c

histogram.o: histogram.c histogram.h
	$(CC) -c histogram.c

clean:
	rm -f $(binaries) *.o

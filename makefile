CC=gcc
binaries=galtonboard galtonboard_debug

make: main.c histogram.c
	$(CC) -o galtonboard main.c histogram.c

debug: main.c histogram.c
	$(CC) -Wall -o galtonboard_debug main.c histogram.c

clean:
	rm -f $(binaries) *.o
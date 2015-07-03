CFLAGS=-Wall -g
CC=gcc

all: normal

normal:
	$(CC) $(CFLAGS) queue.c main.c -o queue 

silent:
	$(CC) $(CFLAGS) queue.c main.c -o queue -DSILENT

verbose:
	$(CC) $(CFLAGS) queue.c main.c -o queue -DCAN_I_HAZ_DEBUG

clean:
	rm queue

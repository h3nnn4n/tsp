CFLAGS=-Wall -g
CC=gcc

all: bnb

bnb:
	$(CC) $(CFLAGS) queue.c main.c -o queue

verbose:
	$(CC) $(CFLAGS) queue.c main.c -o queue -DCAN_I_HAZ_DEBUG

clean:
	rm queue

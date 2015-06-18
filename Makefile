CFLAGS=-Wall -g
CC=gcc

all: queue_test

queue_test:
	$(CC) $(CFLAGS) queue.c main.c -o queue

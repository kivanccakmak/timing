CC=gcc

CFLAGS += -g
CFLAGS += -Wall

default: all

all: lib test

lib:
	$(CC) $(CFLAGS) -c timing.c

test:
	$(CC) $(CFLAGS) main.c timing.o -o timing -DTEST=1 -lpthread

memtest: lib test
	valgrind --leak-check=full ./timing

clean:
	rm -rf *.o
	rm -rf timing

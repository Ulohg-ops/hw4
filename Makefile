CC = gcc

all: p1 p2 p3

p1: p1.c sem.c
	$(CC) $(CFLAGS) -o p1 p1.c sem.c

p2: p2.c sem.c
	$(CC) $(CFLAGS) -o p2 p2.c sem.c

p3: p3.c sem.c
	$(CC) $(CFLAGS) -o p3 p3.c sem.c

clean:
	rm -f p1 p2 p3

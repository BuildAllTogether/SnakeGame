CC = gcc
CFLAGS = -Wall -std=c11
LDFLAGS := -lncursesw

SOURCEFILES := main.c snakes.c

all: snakes

board.o: board.c
	$(CC) -c $(CFLAGS) board.c

snakes.o: snakes.c
	$(CC) -c $(CFLAGS) snakes.c

food.o: food.c
	$(CC) -c $(CFLAGS) food.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

snakes: snakes.o food.o board.o main.o
	$(CC) $(CFLAGS) -o snakes snakes.o food.o board.o main.o $(LDFLAGS) -lpthread



.PHONY: clean
clean:
	rm -r -f snakes *.o *~ main

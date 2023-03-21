CC = gcc
CFLAGS = -Wall -std=c11
LDFLAGS := -lncursesw

SOURCEFILES := main.c snakes.c

all: snakes

snakes.o: snakes.c
	$(CC) -c $(CFLAGS) snakes.c

food.o: food.c
	$(CC) -c $(CFLAGS) food.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

snakes: snakes.o food.o main.o
	$(CC) $(CFLAGS) -o snakes snakes.o food.o main.o $(LDFLAGS) -lpthread



.PHONY: clean
clean:
	rm -r -f snakes *.o *~ main

OS := $(shell uname -s)

ifeq ($(OS), Darwin) 
  CUNIT_PATH_PREFIX = /usr/local/Cellar/cunit/2.1-3/
  CUNIT_DIRECTORY = cunit
endif
ifeq ($(OS), Linux) 
  CUNIT_PATH_PREFIX = /util/CUnit/
  CUNIT_DIRECTORY = CUnit/
endif

CC = gcc
CFLAGS = -g -Wall -std=c11 
LDFLAGS := -lncursesw

SOURCEFILES := main.c snakes.c

all: snakes

board.o: board.c
	$(CC) -c $(CFLAGS) board.c

snakes.o: snakes.c
	$(CC) -c $(CFLAGS) snakes.c

food.o: food.c
	$(CC) -c $(CFLAGS) food.c

test.o: test.c
	$(CC) -c $(FLAGS) -I $(CUNIT_PATH_PREFIX)include/$(CUNIT_DIRECTORY) test.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

snakes: snakes.o food.o board.o main.o
	$(CC) $(CFLAGS) -o snakes snakes.o food.o board.o main.o $(LDFLAGS) -lpthread

tests:  snakes.o food.o board.o test.o
	gcc -Wall -L $(CUNIT_PATH_PREFIX)lib -I $(CUNIT_PATH_PREFIX)include/$(CUNIT_DIRECTORY) -o tests snakes.o food.o board.o test.o -lcunit $(LDFLAGS)


.PHONY: clean
clean:
	rm -r -f snakes *.o *~ main tests

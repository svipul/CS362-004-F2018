CFLAGS= -Wall -fpic -coverage -lm -std=c99

adventurer.o: adventurer.h adventurer.c
	gcc -c adventurer.c -g $(CFLAGS)

cards: adventurer.o
	gcc shared -o cards.so adventurer.o $(CFLAGS)

all: cards

clean:
	rm -f *.o

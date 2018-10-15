CFLAGS= -Wall -fpic -coverage -lm -std=c99

cardHelper.o: cardHelper.h cardHelper.c
	gcc -c cardHelper.c -g $(CFLAGS)

adventurer.o: adventurer.h adventurer.c
	gcc -c adventurer.c -g $(CFLAGS)

councilRoom.o: councilRoom.h councilRoom.c
	gcc -c councilRoom.c -g $(CFLAGS)

mine.o: mine.h mine.c
	gcc -c mine.c -g $(CFLAGS)

remodel.o: remodel.h remodel.c cardHelper.o
	gcc -c remodel.c -g $(CFLAGS)

smithy.o: smithy.h smithy.c cardHelper.o
	gcc -c smithy.c -g $(CFLAGS)

cards: adventurer.o councilRoom.o mine.o remodel.o smithy.o cardHelper.o
	gcc -shared -o cards.so adventurer.o councilRoom.o mine.o remodel.o smithy.o cardHelper.o $(CFLAGS)

all: cards

clean:
	rm -f *.o *.so *.gcno

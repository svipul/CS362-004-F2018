CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g $(CFLAGS)

cards: cards/adventurer.c
	$(MAKE) all -C cards $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o cards
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o cards/cards.so $(CFLAGS)

randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer > randomtestadventurer.out
	gcov -b -c cards/adventurer.c >> randomtestadventurer.out
	cat cards/adventurer.c.gcov >> randomtestadventurer.out


randomtestcard1: randomtestcard1.c dominion.o rngs.o cards
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o cards/cards.so $(CFLAGS)

randomtestcard1.out: randomtestcard1
	./randomtestcard1 > randomtestcard1.out
	gcov -b -c cards/mine.c >> randomtestcard1.out
	cat cards/mine.c.gcov >> randomtestcard1.out

randomtestcard2: randomtestcard2.c
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o cards/cards.so $(CFLAGS)

randomtestcard2.out: randomtestcard2
	./randomtestcard2 &> randomtestcard2.out
	gcov -b -c cards/smithy.c >> randomtestcard2.out
	cat cards/smithy.c.gcov >> randomtestcard2.out


playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o cards/cards.so  $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o cards/cards.so $(CFLAGS)

all: playdom player 
	+$(MAKE) all -C cards

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

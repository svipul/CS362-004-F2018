CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
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
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)


### keyesmcs@ test build rules ###


## UNIT TESTS ##

# assertThat, test helper rules
assertThat.o: assertThat.c assertThat.h
	gcc -c assertThat.c -g $(CFLAGS)

# Unit test *.o rules
unittest1.o: unittest1.c unittest1.h assertThat.o
	gcc -c unittest1.c -g $(CLFAGS)

unittest2.o: unittest2.c unittest2.h assertThat.o
	gcc -c unittest2.c -g $(CFLAGS)

unittest3.o: unittest3.c unittest3.h assertThat.o
	gcc -c unittest3.c -g $(CLFAGS)

unittest4.o: unittest4.c unittest4.h assertThat.o
	gcc -c unittest4.c -g $(CFLAGS)

# Card test *.o rules
cardtest1.o: cardtest1.c cardtest1.h assertThat.o
	gcc -c cardtest1.c -g $(CFLAGS)

cardtest2.o: cardtest2.c cardtest2.h assertThat.o
	gcc -c cardtest2.c -g $(CFLAGS)

cardtest3.o: cardtest3.c cardtest3.h assertThat.o
	gcc -c cardtest3.c -g $(CFLAGS)

cardtest4.o: cardtest4.c cardtest4.h assertThat.o
	gcc -c cardtest4.c -g $(CFLAGS)

testSuite: testSuite.c unittest1.o unittest2.o unittest3.o unittest4.o \
    cardtest1.o cardtest2.o cardtest3.o cardtest4.o dominion.o
	gcc -o testSuite.exe testSuite.c -g dominion.o unittest1.o unittest2.o \
	    unittest3.o unittest4.o cardtest1.o cardtest2.o cardtest3.o \
	    cardtest4.o assertThat.o rngs.o $(CFLAGS)


## RANDOM TESTS ##


randomtestadventurer.exe: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer.exe randomtestadventurer.c -g dominion.o \
	    rngs.o $(CFLAGS)

randomtestcard1.exe: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1.exe randomtestcard1.c -g dominion.o \
	    rngs.o $(CFLAGS)

randomtestcard2.exe: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2.exe randomtestcard2.c -g dominion.o \
	    rngs.o $(CFLAGS)


### end keyesmcs@ test build rules ###

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

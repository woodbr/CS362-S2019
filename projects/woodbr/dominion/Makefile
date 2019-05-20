CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

randomtestutil.o: randomtestutil.c
	gcc -c randomtestutil.c -g $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o interface.o randomtestutil.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o interface.o randomtestutil.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o interface.o randomtestutil.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o interface.o randomtestutil.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o interface.o randomtestutil.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o interface.o randomtestutil.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestresults: randomtestcard1 randomtestcard2 randomtestadventurer
	printf '*** RANDOM TEST CARD 1 ***\n' > randomtestresults.out
	./randomtestcard1 >/dev/null 2>&1
	gcov -b -c dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	printf '*** RANDOM TEST CARD 2 ***\n' >> randomtestresults.out
	./randomtestcard2 >/dev/null 2>&1
	gcov -b -c dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	printf '*** RANDOM TEST ADVENTURER ***\n' >> randomtestresults.out
	./randomtestadventurer >/dev/null 2>&1
	gcov -b -c dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe randomtestcard1 randomtestcard2 randomtestadventurer

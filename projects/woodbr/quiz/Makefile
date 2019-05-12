CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme testme.c -g $(CFLAGS)

runtests: testme
	-./testme
	gcov testme.c > randomtestresult.out
	cat testme.c.gcov >> randomtestresult.out

clean:
	rm -f *.o testme  *.gcov *.gcda *.gcno *.so *.out

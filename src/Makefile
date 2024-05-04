CC=gcc
CFLAGS= -Wall -c
LDFLAGS= -Wall


cache: main.o cache.o stats.o
	$(CC) -o cache main.o cache.o stats.o $(LDFLAGS)

main.o: main.c cache.h stats.h
	$(CC) main.c $(CFLAGS)

cache.o: cache.c cache.h
	$(CC) cache.c $(CFLAGS)

stats.o: stats.c stats.h
	$(CC) stats.c $(CFLAGS)

clean:
	rm -f *.o

run:
	./cache
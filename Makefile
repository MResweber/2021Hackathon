# Makefile

CC = gcc
CFLAGS = -Wall

FoI: screen.o game.o
	$(CC) $(CFLAGS) -o FoI screen.o game.o -lncurses


screen: screen.c screen.h game.h
	$(CC) $(CFLAGS) -c screen.c


game: game.c game.h
	$(CC) $(CFLAGS) -c game.c

clean:
	rm -f FoI *.o
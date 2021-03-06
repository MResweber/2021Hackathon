# Makefile

CC = gcc
CFLAGS = -Wall

#default: Delver

Delver: game.o screen.o
	$(CC) $(CFLAGS) -o Delver game.o screen.o -lncurses

game: game.c screen.h
	$(CC) $(CFLAGS) -c game.c

screen: screen.c screen.h
	$(CC) $(CFLAGS) -c screen.c

clean:
	rm -f Delver *.o
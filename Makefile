# Makefile

CC = gcc
CFLAGS = -Wall

#default: Delver

Delver: main.o screen.o game.o mapFactory.o
	$(CC) $(CFLAGS) -o Delver main.o screen.o game.o mapFactory.o -lncurses

main: main.c screen.h
	$(CC) $(CFLAGS) -c main.c

screen: screen.c screen.h game.h mapFactory.h
	$(CC) $(CFLAGS) -c screen.c


game: game.c game.h mapFactory.h
	$(CC) $(CFLAGS) -c game.c


mapFactory: mapFactory.c mapFactory.h
	$(CC) $(CFLAGS) -c mapFactory.c

clean:
	rm -f Delver *.o
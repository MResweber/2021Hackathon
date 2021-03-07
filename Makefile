# Makefile

CC = gcc
CFLAGS = -Wall

#default: Delver

FoI: screen.o game.o
	$(CC) $(CFLAGS) -o FoI screen.o game.o -lncurses

#main: main.c screen.h
#	$(CC) $(CFLAGS) -c main.c

screen: screen.c screen.h game.h
	$(CC) $(CFLAGS) -c screen.c


game: game.c game.h
	$(CC) $(CFLAGS) -c game.c


#mapFactory: mapFactory.c mapFactory.h
#	$(CC) $(CFLAGS) -c mapFactory.c

clean:
	rm -f Delver *.o
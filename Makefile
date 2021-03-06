# Makefile

CC = gcc
CFLAGS = -Wall

#default: Delver

Delver: main.o screen.o
	$(CC) $(CFLAGS) -o Delver main.o screen.o -lncurses

main: main.c screen.h
	$(CC) $(CFLAGS) -c main.c

screen: screen.c screen.h
	$(CC) $(CFLAGS) -c screen.c

clean:
	rm -f Delver *.o
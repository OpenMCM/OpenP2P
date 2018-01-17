CC=gcc
CFLAGS=-Wall

all: finder/finder

finder/finder: finder/main.c
		$(CC) finder/main.c -o finder/finder set/set.c

clean:
		rm finder/finder

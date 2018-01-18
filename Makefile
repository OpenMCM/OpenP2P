CC=gcc
CFLAGS=-Wall -Wpedantic -Wextra

all: finder/finder

finder/finder: finder/main.c
		$(CC) $(CFLAGS) finder/main.c set/set.c -o finder/finder

clean:
		rm finder/finder

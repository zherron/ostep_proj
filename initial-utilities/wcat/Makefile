SRCS = wcat.c
TRGS = wcat
CC = gcc
OPTS = -Wall -Werror

wcat: wcat.o
	$(CC) -o wcat wcat.o

wcat.o: wcat.c
	$(CC) -c wcat.c $(OPTS)


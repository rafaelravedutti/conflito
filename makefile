CC=gcc
CFLAGS=-Wall

all: conflito

conflito: conflito.c
	${CC} -o $@ $^ ${CFLAGS}

clean:
	rm -f conflito

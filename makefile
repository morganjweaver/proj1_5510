CC=gcc
CFLAGS=-I.

all: fingerserver fingerclient

server: fingerserver.o
	$(CC) -o fingerserver fingerserver.o -I.

client: client.o
	$(CC) -o fingerclient fignerclient.o -I.

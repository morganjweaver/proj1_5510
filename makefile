CC=gcc
CFLAGS=-I.

all: server client

server: server.o
	$(CC) -o server server.o -I.

client: client.o
	$(CC) -o client client.o -I.

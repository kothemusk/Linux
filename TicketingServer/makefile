all: client pa2.out
CC = gcc
client: client.c
	$(CC) -o client $^
pa2.out: server.c
	$(CC) -o pa2.out $^ -lpthread
clean:
	rm client pa2.out

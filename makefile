CC      = gcc
CFLAGS  = -g -std=gnu11 -Werror -Wall -Wextra -Wpedantic \
          -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition

OBJ 	= tcp-server.o tcp-client.o

.PHONY: all clean

all: tcp-server tcp-client

tcp-server: tcp-server.o
	$(CC) -o tcp-server tcp-server.o

tcp-client: tcp-client.o
	$(CC) -o tcp-client tcp-client.o

tcp-server.o: tcp-server.c tcp-com.h
	$(CC) $(CFLAGS) -c tcp-server.c

tcp-client.o: tcp-client.c tcp-com.h
	$(CC) $(CFLAGS) -c tcp-client.c

clean: 
	rm -f tcp-server tcp-client $(OBJ)
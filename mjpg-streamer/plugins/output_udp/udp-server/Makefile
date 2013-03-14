

CC=gcc
CFLAGS=-s -Wall

.SUFFIXES: .c .o

ALL = client server
all: $(ALL)

CLIENT_OBJ=udp-client.o udp.o
SERVER_OBJ=udp-server.o

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 
	
server: $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 
	
.c.o:
	$(CC) $(CFLAGS) -o $@ -c $*.c
	
.PHONY: clean
clean:
	rm -f *.o
	rm -f $(ALL)
	

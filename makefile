##
# Proyecto Final
#
# @file
# @version 0.1

CC = gcc
CFLAGS = -Wall -std=c2x
LIBS = -pthread
TARGET = cliente servidor

all: $(TARGET)

cliente:
	$(CC) $(CFLAGS) $(LIBS) -o cliente cliente.c ccliente.c

servidor:
	$(CC) $(CFLAGS) $(LIBS) -o servidor servidor.c sservidor.c


clean:
	rm -rf $(TARGET) *.o

.PHONY: all clean

# end

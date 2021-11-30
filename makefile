##
# Proyecto Final
#
# @file
# @version 0.1

CC = gcc
CFLAGS = -Wall -std=c2x -pthread
OBJ = cliente servidor

default: all

all: $(OBJ)

cliente:
	gcc -std=c2x -pthread -o cliente cliente.c ccliente.c
servidor:
	gcc -std=c2x -pthread -o servidor servidor.c sservidor.c

clean:
	rm -rf $(OBJ)

.PHONY: all clean

# end

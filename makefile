##
# Proyecto Final
#
# @file
# @version 0.1

CC = gcc
LIBS = -pthread
INC_DIR = headers/
CFLAGS = -Wall -I$(INC_DIR) -std=c2x

CLIENTE_DIR = core/cliente
SERVIDOR_DIR = core/servidor

SRC_CLIENTE = $(CLIENTE_DIR)/ccliente.c $(CLIENTE_DIR)/cliente.c
SRC_SERVIDOR = $(SERVIDOR_DIR)/servidor.c $(SERVIDOR_DIR)/sservidor.c $(SERVIDOR_DIR)/cmd_parser.c

OBJS = $(OBJ_CLIENTE) $(OBJ_SERVIDOR)

TARGET = cliente servidor

all: clean $(TARGET)

servidor:
	$(CC) $(LIBS) $(CFLAGS) $(SRC_SERVIDOR)  -o servidor

cliente:
	$(CC) $(LIBS) $(CFLAGS) $(SRC_CLIENTE)  -o cliente


clean:
	rm -rf $(TARGET) *.o

.PHONY: all clean

# end

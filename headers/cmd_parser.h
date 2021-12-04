#ifndef CMD_PARSER_H
#define CMD_PARSER_H
#include "sservidor.h"

#define size 1024

typedef struct cmd_parser {
    char completo_comando[size];
    char comando[size];
    char argumentos[size];
} cmd;

void ejecutar(char * ejecutar, servidor * serv);
void strip_chars(char *str, char strip);

#endif // CMD_PARSER_H

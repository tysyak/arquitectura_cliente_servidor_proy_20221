#ifndef CMD_PARSER_H
#define CMD_PARSER_H

#define size 1024

typedef struct cmd_parser {
    char completo_comando[size];
    char comando[size];
    char argumentos[size];
} cmd;

int ejecutar(char * ejecutar);

#endif // CMD_PARSER_H

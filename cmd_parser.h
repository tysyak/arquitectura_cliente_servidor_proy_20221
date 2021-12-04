#ifndef CMD_PARSER_H
#define CMD_PARSER_H

#define size 1024

typedef struct cmd_parser {
    char completo_comando[size];
    char comando[size];
    char argumentos[size];
} cmd;

void ejecutar(char * ejecutar);
void strip_chars(char *str, char strip);
int spawn (char* program, char** arg_list);

#endif // CMD_PARSER_H

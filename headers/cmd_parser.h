#ifndef CMD_PARSER_H
#define CMD_PARSER_H
#include "sservidor.h"

#define size 1024

/**
 * Estructura simple para ejecutar un comando
 */
typedef struct cmd_parser {
    char completo_comando[size];///< El comando completo
    char comando[size];///< El comando sin argumento
    char argumentos[size];///<  Los Argumentos del comado
} cmd;

/**
 * Limpia, ejecuta y pasa la salida del comando al cliente conectado al servidor
 * @param[in] ejecutar El comando a ejecutar
 * @param[in] srv La estructura sServidor a donde se enviará la ejecución del comando al cliente
 */
void ejecutar(char * ejecutar, servidor * serv);

/**
 * Elimina caracteres de una cadena 
 * @param[in] *str La cadena objetivo
 * @param[in] strp El caracter a eliminar
 */
void strip_chars(char *str, char strip);

#endif // CMD_PARSER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd_parser.h"

int ejecutar(char *ejecutar) {
  int itera = 0;
  int itera_aux = 0;
  cmd *comando = malloc(sizeof(cmd) * 3);
  unsigned int tamanio_cadena;
  int aux_flag = 0;
  char letter = ' ';
  char set_arg[size];
  char *args[3];

  strcpy(comando->completo_comando, ejecutar);
  tamanio_cadena = strlen(comando->completo_comando);

  while (itera <= tamanio_cadena) {
    letter = comando->completo_comando[itera];
    if (letter == ' ') {
        aux_flag = 1;
        itera++;
        letter = comando->completo_comando[itera];
    }
    if (aux_flag == 0)
      comando->comando[itera] = letter;
    else {
        printf("%c", letter);
        comando->argumentos[itera_aux] = letter;
        itera_aux++;
    }
    itera++;
  }
  args[0] = comando->comando;
  args[2] = NULL;
  if (strlen(comando->argumentos) == 0) {
    args[1] = NULL;
  } else {
      args[1] = comando->argumentos;
  }
  if (execvp(comando->comando, args) == -1) {
    perror("execve");
    exit(EXIT_FAILURE);
  }
  puts("shouldn't get here");
  exit(EXIT_SUCCESS);
  return 0;
}

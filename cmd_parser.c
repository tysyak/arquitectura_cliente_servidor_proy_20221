#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "cmd_parser.h"

void strip_chars(char *str, char strip)
{
    char *p, *q;
    for (q = p = str; *p; p++)
        if (*p != strip)
            *q++ = *p;
    *q = '\0';
}

int spawn (char* program, char** arg_list)
{
	pid_t child_pid;
	child_pid = fork ();
	if (child_pid != 0) /* This is the parent process. */
		return child_pid;
	else {
		execvp (program, arg_list);
	}
}

void ejecutar(char *ejecutar) {
  char *exe = ejecutar;
  int itera = 0;
  int itera_aux = 0;
  cmd *comando = malloc(sizeof(cmd) * 3);
  unsigned int tamanio_cadena;
  int aux_flag = 0;
  char letter = ' ';
  char *args[3];
  strip_chars(exe, '\n');

  strcpy(comando->completo_comando, exe);
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

  spawn(comando->comando, args);

}

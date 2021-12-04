#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "cmd_parser.h"
#include "sservidor.h"

void strip_chars(char *str, char strip)
{
    char *p, *q;
    for (q = p = str; *p; p++)
        if (*p != strip)
            *q++ = *p;
    *q = '\0';
}

void  ejecutar(char *ejecutar, servidor * serv) {
  char *exe = ejecutar;
  cmd *comando = malloc(sizeof(cmd) * 3);
  int itera = 0;
  int itera_aux = 0;
  char letter = ' ';
  unsigned int tamanio_cadena;
  int aux_flag = 0;

  FILE *fp;
  char path[size];

  strip_chars(exe, '\n');

  strcpy(comando->completo_comando, exe);
  tamanio_cadena = strlen(comando->completo_comando);


  while(itera <= tamanio_cadena) {
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
  if (strcmp(comando->comando, "cd")==0) {
      chdir(comando->argumentos);
  } else {
    fp = popen(comando->completo_comando, "r");
    if (fp == NULL) {
      printf("Failed to run command\n");
      exit(1);
    }


    /* Read the output a line at a time - output it. */

    char some[99999];
    memset(some,0,sizeof(some));
    while (fgets(path, sizeof(path), fp) != NULL) {
      strcat(some,path);
    }
    serv->bytes = send(serv->client_fd, some, sizeof(some), 0);
    printf("%s", some);
  }
    pclose(fp);

  printf("> ");
}

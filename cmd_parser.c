#include <unistd.h>
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

  FILE *fp;
  char path[size];

  strip_chars(exe, '\n');

  strcpy(comando->completo_comando, exe);

  fp = popen(comando->completo_comando, "r");
  if (fp == NULL) {
    printf("Failed to run command\n");
    exit(1);
  }

  /* Read the output a line at a time - output it. */
  while (fgets(path, sizeof(path), fp) != NULL) {
      serv->bytes = send(serv->client_fd, path, sizeof(path), 0);
  }
  pclose(fp);
  printf("> ");
  /* close */


}

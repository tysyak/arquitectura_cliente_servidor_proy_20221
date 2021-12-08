#include "ccliente.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

int main(int argc, char *const argv[]) {

  if (argc != 3) {
    printf("\e[31mError: Fallo en pasar parametros\e[0m");
    printf("\nVerifique los parametros dados\n");
    return 1;
  }
  // Verificamos levemente los argumonetos que nos pasaron

  char *ip = argv[1];
  char *p; // auxiliar para strtol
  const int puerto = strtol(argv[2], &p, 10);
  // Asignamos el ip como cadena de caracteres y el puerto como entero

  cliente *cli = cliente_new(ip, puerto);
  // Creamos nuestro cliente

  /* Enviamos mensajes al servidor */
  while (strncmp(cli->write_buffer, ":q", 2) != 0) {
    printf("> ");
    strcpy(cli->write_buffer, "\0");
    fgets(cli->write_buffer, size, stdin);
    cli->bytes =
        send(cli->client_fd, cli->write_buffer, sizeof(cli->write_buffer), 0);
    if (cli->bytes == -1)
      perror("\e[31mEl servidor fallo\e[0m\n");
  }

  pthread_join(cli->thread_id, &cli->retval);
  printf("Hasta la próxima");
  close(cli->client_fd);
  // Esperamos a que el hilo termine cerramos la conexión del servidor y terminamos el programa

  return 0;
}

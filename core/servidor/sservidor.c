#include "sservidor.h"
#include "cmd_parser.h"

servidor *servidor_new() {
  int True = 1;

  servidor *serv = malloc(sizeof(servidor));

  unlink("SOCKET SERVER");

  serv->server_fd = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(serv->server_fd, SOL_SOCKET, SO_REUSEADDR, &True, sizeof(int));
  if (serv->server_fd == -1) {
    perror("\e[31mCreación del socket fallo\e[0m\n");
    exit(1);
  } else
    printf("\e[32mExito en la creación del socket\e[0m\n");

  serv->server_addrobj.sin_family = AF_INET;
  serv->server_addrobj.sin_port = htons(PORT);
  serv->server_addrobj.sin_addr.s_addr = htonl(INADDR_ANY);
  // Definimos nuestro formato de dirección

  serv->ret =
      bind(serv->server_fd, (const struct sockaddr *)&serv->server_addrobj,
           sizeof(serv->server_addrobj));
  // Asignamos la dirección especificada por addr al socket al que hace referencia el descriptor.

  if (serv->ret == -1) {
    perror("\e[31mBinding falló\e[0m\n");
    exit(1);
  } else
    printf("\e[32mExito en el Binding\e[0m\n");
  // Verificacmos vincualción

  serv->ret = listen(serv->server_fd, 5);
  if (serv->ret == -1) {
    perror("\e[31mFallo creando el Listening\e[0m\n");
    exit(1);
  } else
    printf("\e[32mExito creando el Listening\e[0m\n");
  // Verificamos Escucha

  return serv;
  // Devolvemos nuestro "servidor"
}

void *thread_function(void *arg) {
  servidor *serv = arg;

  while (strncmp(serv->read_buffer, ":q", 2) != 0) {
    bzero(serv->read_buffer, size);
    serv->bytes = recv(serv->client_fd, serv->read_buffer, size, 0);
    if (serv->bytes == -1) {
      sleep(5);
      perror("\e[31mFallo en la lectura del cliente\e[0m\n");
    } else {
      ejecutar(serv->read_buffer, serv);
      printf("\nCliente> %s", serv->read_buffer);
    }
  }
  // Recibimos lo que el cliente nos envía, mientrasn no sea :q
  pthread_exit(NULL);
}

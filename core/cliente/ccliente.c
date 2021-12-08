#include "ccliente.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

cliente *cliente_new(char *ip, int puerto) {

  cliente *cli = malloc(sizeof(cliente));

  cli->client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (cli->client_fd == -1) {
    perror("\e[31mCreación del socket fallo\e[0m\n");
    exit(1);
  } else
    printf("\e[32mExito en la creación del socket\e[0m\n");

  cli->client_addrobj.sin_family = AF_INET;
  cli->client_addrobj.sin_port = htons(puerto);
  cli->client_addrobj.sin_addr.s_addr = inet_addr(ip);
  // Definimos nuestro formato de dirección, con los datos que se nos otorgo en
  // los argumentos

  cli->ret = connect(cli->client_fd, (struct sockaddr *)&cli->client_addrobj,
                     sizeof(cli->client_addrobj));
  // Nos conectamos al socket del servidor.

  if (cli->ret == -1) {
    perror("\e[31mBinding falló\e[0m: No se halló conexión al servidor\n");
    exit(1);
  } else
      printf("\e[32mExito en el Binding\e[0m\n");
  // Verificacmos vincualción

  bzero(cli->write_buffer, size);
  // Llenamos de 0s el buffer de escritura

  cli->ret = pthread_create(&cli->thread_id, NULL, thread_function, cli);
  // Ejecutamos la conexión en un hilo para permimitir la comunicación bidireccional

  return cli;
  // Devolvemos nuestro "servidor"
}

void *thread_function(void *arg) {
  cliente *cli = arg;
  strcpy(cli->read_buffer, "\0");
  while (strncmp(cli->read_buffer, ":q", 2) != 0) {
    strcpy(cli->read_buffer, "\0");
    cli->bytes = recv(cli->client_fd, cli->read_buffer, size, 0);
    if (cli->bytes == -1)
      perror("\e[31mFallo en la lectura del servidor\e[0m\n");
    else
      printf("%s", cli->read_buffer);
  }
  // Recibimos lo que el cliente nos envía, mientrasn no sea :q
  pthread_exit(NULL);
}

#include "sservidor.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <threads.h>

int main() {

  servidor *serv = servidor_new();

  while (1) {
    int status_cliente = 0;
    bzero(serv->read_buffer, size);
    bzero(serv->write_buffer, size);
    // Llenamos de \0 el buffer de escritura y lectura



    while (status_cliente == 0) {
      printf("\nEsperando Cliente...\n");
      serv->client_len = sizeof(serv->client_addrobj);
      serv->client_fd =
          accept(serv->server_fd, (struct sockaddr *)&serv->client_addrobj,
                 &serv->client_len);
      if (serv->client_fd == -1)
        perror("\e[31mError en la conexión\e[0m\n");
      else {
		  printf("\e[32mConexión exitosa\e[0m\n");
		  status_cliente++;
	  }
    }
	// Estamos a la espera de que el cliente se conecte al socket

    serv->ret = pthread_create(&serv->thread_id, NULL, thread_function, serv);
	// Ejecutamos la conexión en un hilo para permimitir la comunicación bidireccional

    while (strncmp(serv->write_buffer, ":q", 2) != 0) {
      strcpy(serv->write_buffer, "\0");
      printf("\nServidor(tu)>");
      fgets(serv->write_buffer, size, stdin);
      serv->bytes = send(serv->client_fd, serv->write_buffer,
                         sizeof(serv->write_buffer), 0);

      if (serv->bytes == -1)
        perror("\e[31mEl servidor fallo\e[0m\n");
    }
	// El servidor se comunica si el Usuario (del servidor) quiere

    pthread_join(serv->thread_id, &serv->retval);
    printf("Hasta la próxima");
    close(serv->client_fd);
	// Esperamos a que el hilo termine cerramos la conexión del servidor y terminamos el programa
  }

  close(serv->server_fd);
  return 0;
}

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/in.h>
#include "sservidor.h"

int main()
{

	servidor * serv = servidor_new();

	while(1)
	{
		bzero(serv->read_buffer, size);
		bzero(serv->write_buffer, size);

		printf("\nEsperando Cliente...\n");
		serv->client_len=sizeof(serv->client_addrobj);
		serv->client_fd = accept(serv->server_fd, (struct sockaddr *)&serv->client_addrobj, &serv->client_len);

		if(serv->client_fd == -1)
			perror("\e[31mError en la conexión\e[0m\n");
		else
			printf("\e[32mConexión exitosa\e[0m\n");

		serv->ret = pthread_create(&serv->thread_id, NULL, thread_function, serv);
		while(strncmp(serv->write_buffer, ":q", 2) != 0 )
		{
			strcpy(serv->write_buffer, "\0" );
			printf("\nServidor(tu)>");
			fgets(serv->write_buffer, size, stdin);
			serv->bytes = send(serv->client_fd, serv->write_buffer, sizeof(serv->write_buffer), 0);

			if(serv->bytes == -1)
				perror("\e[31mEl servidor fallo\e[0m\n");
		}

		pthread_join(serv->thread_id, &serv->retval);
		printf("Hasta la próxima");
		close(serv->client_fd);
	}

	close(serv->server_fd);
    return 0;
}


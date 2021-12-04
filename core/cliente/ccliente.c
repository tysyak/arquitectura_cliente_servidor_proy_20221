#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include "ccliente.h"

cliente * cliente_new(char * ip, int puerto) {

    cliente* cli = malloc(sizeof(cliente));

    cli->client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(cli->client_fd == -1)
		perror("\e[31mCreación del socket fallo\e[0m\n");
	else
		printf("\e[32mExito en la creación del socket\e[0m\n");

    cli->client_addrobj.sin_family = AF_INET;
	cli->client_addrobj.sin_port = htons(puerto);
	cli->client_addrobj.sin_addr.s_addr = inet_addr(ip);

    cli->ret = connect(cli->client_fd, (struct sockaddr *)&cli->client_addrobj, sizeof(cli->client_addrobj) );

	if(cli->ret == -1)
		perror("\e[31mBinding falló\e[0m\n");
	else
		printf("\e[32mExito en el Binding\e[0m\n");

    bzero(cli->write_buffer, size);
    bzero(cli->write_buffer, size);

    cli->ret = pthread_create(&cli->thread_id, NULL, thread_function, cli);

    return cli;
}

void * thread_function(void *arg)
{
    cliente * cli = arg;
	strcpy(cli->read_buffer, "\0" );
	while( strncmp(cli->read_buffer, ":q", 2) != 0 )
	{
		strcpy(cli->read_buffer, "\0" );
		cli->bytes = recv(cli->client_fd, cli->read_buffer, size, 0);
		if(cli->bytes == -1)
			perror("\e[31mFallo en la lectura del servidor\e[0m\n");
		else
			printf("%s", cli->read_buffer);
	}
	pthread_exit(NULL);
}

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h>
#include "ccliente.h"


int main (int argc, char* const argv[])
{

    if (argc != 3) {
        printf("\e[31mError: Fallo en pasar parametros\e[0m");
        printf("\nVerifique los parametros dados\n");
        return 1;
    }
    char * ip = argv[1];
    char * p;
    const int puerto = strtol(argv[2], &p, 10);


    cliente * cli = cliente_new(ip, puerto);

    while(strncmp(cli->write_buffer, ":q", 2) != 0 )
    {
        strcpy(cli->write_buffer, "\0" );
        printf("Cliente(tu)>");
        fgets(cli->write_buffer, size, stdin);
        cli->bytes = send(cli->client_fd, cli->write_buffer, sizeof(cli->write_buffer), 0);
        if(cli->bytes == -1)
            perror("\e[31mEl servidor fallo\e[0m\n");
    }

    pthread_join(cli->thread_id, &cli->retval);
    printf("Hasta la próxima");
	close(cli->client_fd);

    return 0;
}

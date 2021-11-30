#ifndef CCLIENTE_H
#define CCLIENTE_H

#include<netinet/in.h>
#include<pthread.h>

#define size 1024

typedef struct cCliente {
    char read_buffer[size];
    char write_buffer[size];
    int client_fd;
    int ret;
    int bytes;
    struct sockaddr_in client_addrobj;
    void *retval;
    pthread_t thread_id;
} cliente;

cliente * cliente_new(char* ip, int puerto);
void * thread_function(void *arg);

#endif // CCLIENTE_H

#ifndef SSERVIDOR_H
#define SSERVIDOR_H

#include <pthread.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define size 1024
#define PORT 3490

typedef struct sServidor {
	char write_buffer[size];
	char read_buffer[size];
	void *retval;
	pthread_t thread_id;
	int server_fd;
    int client_fd;
    int ret;
    int bytes;
    socklen_t client_len;
	struct sockaddr_in server_addrobj;
    struct sockaddr_in client_addrobj;

} servidor;


servidor* servidor_new();
void * thread_function(void * arg);

#endif // SSERVIDOR_H

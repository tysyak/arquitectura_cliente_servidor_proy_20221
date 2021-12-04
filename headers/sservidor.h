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

/**
 * Estructura encargada de instaciar el servidor
 */
typedef struct sServidor {
  char write_buffer[size]; ///< Buffer de lectura
  char read_buffer[size]; ///< Buffer de escritura
  void *retval; ///< Estado del Hilo
  pthread_t thread_id; ///< Id del Hilo de ejecución
  int server_fd; ///< fd del servidor
  int client_fd; ///< fd del cliente
  int ret; ///< estado del hilo
  int bytes; ///< mensaje enviado
  socklen_t client_len; ///< Tamaño del socket del cliente
  struct sockaddr_in server_addrobj; ///< socket del servidor
  struct sockaddr_in client_addrobj; ///<socket del cliente

} servidor;

/**
 * Constructor por defecto del servidor.
 *
 * @param[out] Una estructura de tipo sServidor
 */
servidor* servidor_new();

/**
 * Función que se ejecuta en un hilo de ejecución y asi implementar
 * la comunicación bidirecciónal Cliente servidor
 */
void * thread_function(void * arg);

#endif // SSERVIDOR_H

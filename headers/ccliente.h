/// @file ccliente.h
#ifndef CCLIENTE_H
#define CCLIENTE_H

#include<netinet/in.h>
#include<pthread.h>

#define size 1024

/**
 * Almacena los buffer de entrada y salida para poder implementar el cliente
 */
typedef struct cCliente {
    char read_buffer[size]; ///< Buffer de lectura
    char write_buffer[size]; ///< Buffer de escritura
    int client_fd; ///< El descriptor del cliente
    int ret; ///< Verificador de Vinculo (BINDING)
    int bytes; ///<
    struct sockaddr_in client_addrobj; ///< Socket del cliente
    void *retval; ///< Ver mensajes
    pthread_t thread_id; ///< ID de hilo de ejecución para comunicación bidireccional
} cliente;

/**
 * Constructor por defecto del cliente, donde
 * este generea el Biding y el  socket
 * inicial.
 * @param[in] *ip La IP del servidor a conectarse
 * @param[in] puerto El puerto a conectarse
 * @param[out] Una estructura de tipo cCliente
*/
cliente * cliente_new(char* ip, int puerto);
/**
 * Función que se ejecuta en un hilo de ejecución y asi implementar
 * la comunicación bidirecciónal Cliente servidor
 */
void * thread_function(void *arg);

#endif // CCLIENTE_H

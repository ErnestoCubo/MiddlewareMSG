#ifndef  _UTILS_H_
#define  _UTILS_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

//Definiciones de los paquetes y los códigos de errores
#define ERROR		-1
#define SYNC_ACK 	 1
#define ACK 	 	 0
#define SYNC	 	 2
#define END		 3

//Estructura que define el mensaje
typedef struct msg_t{

	int type;
	int len;
}msg_t;

int initServer(int port);
int initClient(char* host, int port);
int waitForConnections(int sock_fd);
void sendMSG(int socket, const void* data, int dataLen);
void recvMSG(int socket, void** data, int* dataLen);
void closeConnections(int socket_fd);

#endif
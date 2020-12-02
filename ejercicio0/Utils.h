#ifndef  _UTILS_H_
#define  _UTILS_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <map>
#include <list>
#include <thread>

//Definiciones de los paquetes y los códigos de errores
#define ERROR		-1
#define SYNC_ACK 	 1
#define ACK 	 	 0
#define SYNC	 	 2
#define END		 3

typedef struct dataPacket_t {
	int dataSize;
	char* data;

}dataPacket_t;

//Estructura que define el mensaje
typedef struct connection_t {
	int clientID;
	int socket_fd;
	bool alive;

	//Se crea una lista de mensajes ya que se van a estar legando mensajes de manera asincrona
	std::list<dataPacket_t*> * buffer;
}connection_t;

int initServer(int port);
int initClient(char* host, int port);
int waitForConnections(int sock_fd);
void sendMSG(int socket, const void* data, int dataLen);
void recvMSG(int socket, void** data, int* dataLen);
void closeConnections(int socket_fd);

#endif
#ifndef  _UTILS_H_
#define  _UTILS_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

int initServer(int port);
int initClient(char* host, int port);
int waitForConnections(sock_fd);
void sendMSG(int socket, const void* data, int dataLen);

#endif
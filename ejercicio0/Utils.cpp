#include "Utils.h"

//Método que se encarga de inicializar el servidor y abrir el socket
int initServer(int port) {

	//Descriptor de ficheros del socket que se abre a la escucha
	int sock_fd;
	//Inicialización de una variable tipo socket
	sock_fd = sockect(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		printf("Hubo un error al crear el socket");
	}
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	//Se reciben funciones de cualquier dirección
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	/*La función htons asegura que los datos recibidos se van 
	a poder interpretar en cualquier switch máquina, 
	transforma los datos de local a red etc*/
	serv_addr.sin_port = htons(port);

	int option = 1;
	setsockopt(sock_fd, SOL_SOCKET,
		(SO_REUSEPORT | SO_REUSEADOR),
		&option, sizeof(option));
	
	//La función bind es la encargada de arbir finalmente el puerto
	if (bind(sock_fd, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0) {
		printf("Error al realizar binding");
	}
	
	//Máximo de 5 peticiones a la espera para evitar el DDoS
	listen(sock_fd, 5);
	return sock_fd;
}
int initClient(char* host, int port) {



}

/*Función que realiza la espera hasta que ocurra la primera conexión y retorna el nuevo
descriptor de fichero perteneciente a la nueva conexión creada*/
int waitForConnections(sock_fd) {
	
	struct sockaddr_in cli_addr;
	sock_len = sizeof(cli_addr);
	int newsock_fd = accept(sock_fd,
		(struct sockaddr *) &cli_addr, &clilen);
	return newsock_fd;
}
void sendMSG(int socket, const void* data, int dataLen) {



}

//Cierra el socket que se encuentra a la escucha
void closeConnections(int socket_fd){

	close(socket_fd);
}

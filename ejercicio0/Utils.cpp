#include "Utils.h"

//Método que se encarga de inicializar el servidor y abrir el socket
int initServer(int port) {

	//Descriptor de ficheros del socket que se abre a la escucha
	int sock_fd;
	//Inicialización de una variable tipo socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
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
		(SO_REUSEPORT | SO_REUSEADDR),
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

/*Esta fucnión realiza los controles de errores necearios a la hora de
establecer la conexión del cliente, se encarga de establecer las variables del
servidor para enlazar la conexión*/
int initClient(char* host, int port) {

	int sock_out = 0;
	struct sockaddr_in serv_addr;

	if ((sock_out = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\nError a la hora de crear el socket");
		return (-1);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	//Conversión de IPsV4 y IPsV6 de texto a binario
	if (inet_pton(AF_INET, host, &serv_addr.sin_addr)<=0) {
		printf("\nError en las direccciones, versiones de ip no suporteadas");
		return (-1);
	}
	if (connect(sock_out, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <= 0) {
		printf("\nError al conectar");
		return -1;
	}
	return sock_out;
}

/*Función que realiza la espera hasta que ocurra la primera conexión y crea el nuevo socket
ya que estos no pueden ser reutilizados*/
int waitForConnections(int sock_fd) {
	
	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);

	//Creación del nuevo socket para retornarl
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

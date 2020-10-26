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

/*Esta función se hace cargo del envío de mensajes haciendo uso de protocolos como el SYN_ACK
además tiene comprobación de errores en caso de que el paquete devuelto no sea el que cierre la conexión
o que no sea del mismo tamaño*/
void sendMSG(int socket, const void* data, int dataLen) {

	short int tag = SYNC;
	int crc = 0;

	//Envío del SYNC

	write(socket, &tag, sizeof(short int));

	//Recibo del SYNC+ACK
	read(socket, &tag, sizeof(short int));

	//Se recibe un paquete distinto al ACK se da el reporte del error y sale
	if (tag != SYN_ACK) {
		printf("ERROR: funcion sendMSG, linea: %d\n", __LINE__);
		closeConnections(socket);
		exit(0);
	}

	//En caso de que i se recibe el paquete se envía el ACK
	tag = ACK;
	write(socket, &tag, sizeof(short int));

	//Envío del tamaño del mensaje una vez realizado el three way handsake
	write(socket, &dataLen, sizeof(int));

	//Envío del mensaje una vez se ha reservado el espacio para este
	write(socket, data, dataLen);

	//Se recibe el tag END
	read(socket, &crc, sizeof(int));

	/*Coprueba el crc en el caso de que el
	crc sea distinto se envía de nuevo un paquete notificando el error al cambiar el tag del
	paquete*/
	if (crc != dataLen) {
		printf("ERROR: funcion sendMSG, linea: %d\n", __LINE__);
		tag = ERROR;
		write(socket, &tag, sizeof(short int));
		closeConnections(socket);
		exit(0);
	}

	//Si el crc esta correcto entonces se devuelve el ACK
	tag = ACK;
	write(socket, &tag, sizeof(short int));
	
	//Se vuelve a recibir e tag END
	read(socket, &tag, sizeof(short int));

	//Comprobación del tag END
	if (tag != END) {
		printf("ERROR: sendMSG, linea: %d \n", __LINE__);
		closeConnection(socket);
		exit(0);
	}
}

/*Función que realiza en el servidor el recibo de los datos o mensajes que envía el cliente esta función 
hace uso del protocolo SYN_ACK antes de establecer la conexión en caso de fallo termina esa coneión entrante*/
void recvMSG(int socket, void** data, int* dataLen) {
	
	short int tag = 0;
	
	//Se recibe el SYNC
	read(socket, &tag, sizeof(short int));

	//Comprueba que el SYN sea el SYNC y no otro tipo de paquete
	if (tag != SYNC) {
		printf("ERROR: sendMSG, linea: %d \n", __LINE__);
		closeConnection(socket);
		exit(0);
	}

	//Respuesta del SYNC con el SYNC+ACK
	tag = SYNC_ACK;
	write(socket, &tag, sizeof(short int));

	//Se recibe el ACK
	read(socket, &tag, sizeof(short int));

	//Se comprueba que sea el ACK y no otro paquete
	if (tag != ACK) {
		printf("ERROR: sendMSG, linea: %d \n", __LINE__);
		closeConnection(socket);
		exit(0);
	}

	//Declaración del buffer
	int tamanioDato = 0;
	char* datos = nullptr;
	int crc = 0;

	//Se recibe el tamaño y se reserva el espacio neceseraio en buffer
	read(socket, &tamanioDato, sizeof(int));
	datos = new char[tamanioDato];

	//Se recibe el mensaje
	crc = read(socket, datos, tamanioDato);

	//Se comunica al cliente que se ha recibido con END y el crc que es el comprobante
	write(socket, &crc, sizeof(int));

	//Se vuelve a recibir ACK en señal que todo esta correcto
	read(socket, &tag, sizeof(short int));
	if (tag != ACK) {
		printf("ERROR: sendMSG, linea: %d \n", __LINE__);
		closeConnection(socket);
		exit(0);
	}

	//Se termina con el enío del end
	tag = END;
	write(socket, &tag, sizeof(short int));
	*data = datos;
	*dataLen = tamanioDato;
}
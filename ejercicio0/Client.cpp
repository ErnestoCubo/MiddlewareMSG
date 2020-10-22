#include"Utils.h"

int main(int arg, char** argv) {
	
	//Inicio de la conexión
	int client_fd = initClient("10.0.5.5", 8081);
	
	//mensaje enviado al servidor
	char* msg = "Hola desde cliente\n";
	int bufferSize = strlen(msg) + 1;

	//Se le pasa primero la longitud del mensaje + '\0'
	write(client_fd, &bufferSize, sizeof(int));

	//Una vez el servidor recibe el tamaño y lo ha reservado se continua pasando el msg
	write(client_fd, msg, bufferSize);
	closeConnections(client_fd);

	return 0;
}
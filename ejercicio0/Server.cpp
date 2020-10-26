#include "Utils.h"
#include <string>

/*Programa principal del servidor primero se incializa en el puerto 8081
una vez incicializado comienza a escuchar y a esperar conexiones*/
int main(int argc, char** argv) {

	int server_fd = initServer(8081);
	int client_fd = waitForConnections(server_fd);

	/*Se usa un primer protocolo en el que primero se recibe el tamaño del mensaje
	para reservar el espacio del mensaje y luego se recibe el mensaje*/
	char* buffer = 0x00;
	int bufferSize = 0;
	
	recvMSG(client_fd, (void**)&buffer, &bufferSize);
	std::cout << "Tamaño del mensaje: " << bufferSize << std::endl;
	std::cout << "Mensaje: " << std::string(buffer) << std::endl;

	//Liberación de las conexiones establecidas
	closeConnections(client_fd);
	closeConnections(server_fd);
	return 0;
}
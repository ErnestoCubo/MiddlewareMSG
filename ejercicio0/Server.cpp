#include "Utils.h"

/*Programa principal del servidor primero se incializa en el puerto 8081
una vez incicializado comienza a escuchar y a esperar conexiones*/
int main(int argc, char** argv) {

	int server_fd = initServer(8081);
	int client_fd = waitForConnections(server_fd);

	//Liberación de las conexiones establecidas
	closeConnections(client_fd);
	closeConnections(server_fd);
	return 0;
}
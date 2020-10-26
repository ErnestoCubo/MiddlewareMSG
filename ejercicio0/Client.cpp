#include"Utils.h"

int main(int arg, char** argv) {
	
	//Inicio de la conexión
	int client_fd = initClient("10.0.5.5", 8081);
	
	//mensaje enviado al servidor
	char* msg = "Hola desde cliente\n";
	int bufferSize = strlen(msg) + 1;
	
	//El mensaje se pasa a través de la fucnión implementada
	sendMSG(client_fd, msg, bufferSize);
	closeConnections(client_fd);

	return 0;
}
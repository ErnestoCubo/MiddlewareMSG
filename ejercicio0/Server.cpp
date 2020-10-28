#include "Utils.h"
#include "Operaciones_imp.h"
#include <string>

/*Programa principal del servidor primero se incializa en el puerto 8081
una vez incicializado comienza a escuchar y a esperar conexiones*/
int main(int argc, char** argv) {

	int server_fd = initServer(8081);
	operaciones_imp* op = new operaciones_imp(server_fd);
	while(!op->salir){
		op->recvOp();
	}
	delete op;	
	return 0;
}
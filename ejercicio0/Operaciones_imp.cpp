#include "Operaciones_imp.h"

operaciones_imp::operaciones_imp(int clientID) {

	client_fd = clientID;
	operacion = new operaciones();
}

/*Método invocado por el servidor que realiza la suma de dos parametros recibidos
por la interfaz stub y esta otra interfaz redirige el resultado de nuevo*/
void operaciones_imp::recvOp() {

	//Declaración de las variables
	char* buffer = 0x00;
	int bufferLen = 0;
	int typeOp = 0;
	recvMSG(client_fd, (void**)&buffer, &bufferLen);
	typeOp = ((int*)buffer)[0];
	switch (typeOp) {
	case OP_SUMA: {
		int param1 = 0;
		int param2 = 0;
		int result = 0;

		//se recibe el primer parametro a sumar
		recvMSG(client_fd, (void**)&buffer, &bufferLen);
		param1 = ((int*)buffer)[0];
		delete[] buffer;

		//Se recibe el segundo parametro a sumar
		recvMSG(client_fd, (void**)&buffer, &bufferLen);
		param2 = ((int*)buffer)[0];
		delete[] buffer;

		//A traves de la clase operaciones se realiza la operacion suma
		result = operacion->suma(param1, param2);

		//Por último se devuelve el resultado al cliente
		sendMSG(client_fd, &result, sizeof(int));
	}
		break;
	case OP_LECTURA: {
		char* fichero = 0x00;
		recvMSG(client_fd, (void**)&buffer, &bufferLen);
		fichero = operacion->leerFichero(buffer);
		delete[] buffer;
		sendMSG(client_fd, &fichero, strlen(fichero) + 1);
		delete[] fichero;
	}
		break;
	case OP_END: {
		this->salir = true;
		delete[] buffer;

	}
		break;
	default:
		std::cout << "No se recibió ninguna operación" << std::endl;
	}
	
}

operaciones_imp::~operaciones_imp() {

	closeConnections(client_fd);
	delete operacion;
}
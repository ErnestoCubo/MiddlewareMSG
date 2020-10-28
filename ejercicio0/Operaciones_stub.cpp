#include "Operaciones_stub.h"
#include "Utils.h"

operaciones_stub::operaciones_stub(){
	socket=initClient("10.0.5.5", 8081);	
}

int operaciones_stub::suma(int a, int b){
	int res=0;
	char* buffer=0x00;
	int bufferLen=0;
	sendMSG(socket, &a, sizeof(int));
	sendMSG(socket, &b, sizeof(int));
	recvMSG(socket, (void**)&buffer, &bufferLen);
	res=((int*)buffer)[0];
	delete[]buffer;
	return res;
}

char* operaciones_stub::leerFichero(char* nombre) {

	char* data = 0x00;
	int dataLen = 0;
	int opType = OP_LECTURA;
	sendMSG(socket, &opType, sizeof(int));
	sendMSG(socket, nombre, strlen(nombre) + 1);
	recvMSG(socket, (void**)&data, &dataLen);
	return data;
}

operaciones_stub::~operaciones_stub() {

	int opType = OP_END;
	sendMSG(socket, &opType, sizeof(int));
}
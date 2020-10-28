#include "Utils.h"
#include "Operaciones_stub.h"

int main(int arg, char** argv) {
	
	int a=atoi(argv[1]);
	int b=atoi(argv[2]);
	int resultado=0;
	char* buffer;
	int bufferSize = 0;

	int client_fd=initClient("10.0.5.5", 8081);

	operaciones_stub* op = new operaciones_stub();
	
	resultado=op->suma(52, 25);
	//char* datoLeido=op->leerFichero("holamundo.txt");
	//std::cout << "Resultado: " << resultado << " fichero leido: " << std::string(datoLeido) << std::endl;
	std::cout << "La suma de: " << a << " mas: " << b << " es " << resultado << std::endl;
	//delete[] datoLeido;
	delete op;
	return 0;
}
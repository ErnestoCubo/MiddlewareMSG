#include "Operaciones.h"
#include <stdio.h>
#include <stdlib.h>

operaciones::operaciones() {

}

int operaciones::suma(int a, int b) {
	return a + b;
}

/*Lee el fichero solo SI EXISTE en caso de que no exista retorna null*/
char* operaciones::leerFichero(char* nombre) {

	int fileLen = 0;
	char* data = 0x00;

	/*Se crea la variable que lee del fichero, una vez le�do el fichero
	se toman refenrencias con la etiqueta END se mueve al final del fichero y con ftell sabemos 
	que tama�o de bytes nos hemos movido con la etiqueta de set nos movemos al inicio, una vez 
	tenemos el tama�o se reserva el tama�o total que ocupan los datos y despu�s con fread lo 
	traspasamos al buffer de datos a�adiendo el \0 luego se cierra el fichero*/
	FILE* f = fopen(nombre, "r");
	fseek(f, 0, SEEK_END);
	fileLen = ftell(f);
	fseek(f, 0, SEEK_SET);
	data = new char[fileLen + 1];
	fread(data, 1, fileLen, f);
	data[fileLen] = '\0';
	fclose(f);
	return data;

}
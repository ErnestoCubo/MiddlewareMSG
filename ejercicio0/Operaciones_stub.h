#ifndef OPERACIONES_STUB_H
#define OPERACIONES_STUB_H

#define	OP_SUMA	1
#define OP_LECTURA	2
#define OP_END	0
class operaciones_stub {
	int socket=0;
public:
	operaciones_stub();
	int suma(int a, int b);
	char* leerFichero(char* nombre);
	~operaciones_stub();
};

#endif // OPERACIONES_STUB_H

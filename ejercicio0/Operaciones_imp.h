#ifndef OPERACIONES_IMP_H
#define OPERACIONES_IMP_H
#include "Operaciones.h"
#include "Utils.h"
#define	OP_SUMA	1
#define OP_LECTURA	2
#define OP_END	0

class operaciones_imp {

	int client_fd = 0;
	operaciones* operacion;
public:
	bool salir = false;
	operaciones_imp(int socket_fd);
	void recvOp();
	~operaciones_imp();
};

#endif // OPERACIONES_IMP_H

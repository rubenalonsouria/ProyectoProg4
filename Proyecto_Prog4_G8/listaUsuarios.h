#ifndef LISTAUSUARIOS_H_
#define LISTAUSUARIOS_H_
#include "usuario.h"
typedef struct listaUsuarios{
	Usuario * aUsuarios;
	int tam;
	int numU;
}ListaUsuarios;

int buscarUsuario(ListaUsuarios lU, char *nom);
void aniadirUsuario(ListaUsuarios *lU, Usuario u);



#endif /* LISTAUSUARIOS_H_ */

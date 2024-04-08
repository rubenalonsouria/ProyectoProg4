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
void aniadirUsuario(ListaUsuarios *lu, Usuario u);
void volcarListaUsuariosAFichero(ListaUsuarios lu, char *nomfich);
void aniadirUsuarioAlFinalDelFichero(Usuario u, char *nomfich);


void eliminarUsuario(ListaUsuarios *lu, int pos);

#endif /* LISTAUSUARIOS_H_ */

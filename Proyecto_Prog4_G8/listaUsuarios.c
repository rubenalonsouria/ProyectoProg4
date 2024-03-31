#include "listaUsuarios.h"
#include <stdio.h>
#include <string.h>
int buscarUsuario (ListaUsuarios lu, char *nom){
	int pos = 0, enc = 0;
	while(!enc && pos <lu.numU){
		if(strcmp(lu.aUsuarios[pos].nombre, nom) == 0){
			enc = 1;
		}else{
			pos++;
		}
	}
	if(enc){
		return pos;
	}else{
		return -1;
	}
}
void aniadirUsuario(ListaUsuarios *lU, Usuario u){
	if(lU->numU < lU->tam){
		lU->aUsuarios[lU->numU] = u;
		lU->numU++;
		printf("Usuario aniadido correctamente\n");
	}else{
		printf("La lista esta completa\n");
	}
	fflush(stdout);
}

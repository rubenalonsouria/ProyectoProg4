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

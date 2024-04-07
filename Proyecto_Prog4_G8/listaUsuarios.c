#include "listaUsuarios.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void volcarFicheroAListaUsuarios(ListaUsuarios *lu, char *nomfich){
	FILE *pf;
	Usuario u;
	pf = fopen(nomfich,"r");
	if(pf!=(FILE*)NULL){
		fscanf(pf,"%d",&lu->tam);
		lu->aUsuarios = (Usuario*)malloc(lu->tam * sizeof(Usuario));
		lu->numU = 0;
		while(fscanf(pf,"%s %s",u.nombre,u.contrasenya) != EOF){ //No ponemos & porque estamos leyendo %s
			lu->aUsuarios[lu->numU] = u;
			lu->numU++;
		}
		fclose(pf);
	}
}

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


void volcarListaUsuariosAFichero(ListaUsuarios lu, char *nomfich){
	FILE *pf;
	int i;
	pf = fopen(nomfich,"w");
	if(pf != (FILE*)NULL){
		fprintf(pf,"%d\n",lu.tam);
		for(i=0;i<lu.numU;i++){
			fprintf(pf,"%s %s\n",lu.aUsuarios[i].nombre,lu.aUsuarios[i].contrasenya);
		}
		fclose(pf);
	}
}

void aniadirUsuarioAlFinalDelFichero(Usuario u, char *nomfich){
	FILE *pf;

	pf = fopen(nomfich,"a");
	if(pf!=(FILE*)NULL){
		fprintf(pf,"%s %s\n",u.nombre,u.contrasenya);
		fclose(pf);
	}
}

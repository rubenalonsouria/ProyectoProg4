#include "listaAdmin.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void volcarFicheroAListaAdmin(ListaAdmin *la, char *nomfich){
	FILE *pf;
	Admin a;
	pf = fopen(nomfich,"r");
	if(pf!=(FILE*)NULL){
		fscanf(pf,"%d",&la->tam);
		la->aAdmin = (Admin*)malloc(la->tam * sizeof(Admin));
		la->numA = 0;
		while(fscanf(pf,"%s %s",a.nombre,a.contrasenya) != EOF){ //No ponemos & porque estamos leyendo %s
			la->aAdmin[la->numA] = a;
			la->numA++;
		}
		fclose(pf);
	}
}

int buscarAdmin (ListaAdmin la, char *nom){
	int pos = 0, enc = 0;
	while(!enc && pos <la.numA){
		if(strcmp(la.aAdmin[pos].nombre, nom) == 0){
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
void aniadirAdmin(ListaAdmin *lA, Admin a){
	if(lA->numA < lA->tam){
		lA->aAdmin[lA->numA] = a;
		lA->numA++;
		printf("Usuario aniadido correctamente\n");
	}else{
		printf("La lista esta completa\n");
	}
	fflush(stdout);
}


void volcarListaAdminAFichero(ListaAdmin la, char *nomfich){
	FILE *pf;
	int i;
	pf = fopen(nomfich,"w");
	if(pf != (FILE*)NULL){
		fprintf(pf,"%d\n",la.tam);
		for(i=0;i<la.numA;i++){
			fprintf(pf,"%s %s\n",la.aAdmin[i].nombre,la.aAdmin[i].contrasenya);
		}
		fclose(pf);
	}
}

void aniadirAdminAlFinalDelFichero(Admin a, char *nomfich){
	FILE *pf;

	pf = fopen(nomfich,"a");
	if(pf!=(FILE*)NULL){
		fprintf(pf,"%s %s\n",a.nombre,a.contrasenya);
		fclose(pf);
	}
}

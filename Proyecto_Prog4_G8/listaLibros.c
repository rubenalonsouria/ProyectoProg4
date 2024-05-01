#include "listaLibros.h"
#include<stdio.h>
#include <string.h>
#include <stdlib.h>

void aniadirLibroaFichero(Libro l){
	FILE *pf;
	pf = fopen("Libros.txt","a");
	if(pf != (FILE*)NULL){
		fprintf("%s %s %s %d \n", l.titulo, l.autor, l.editorial, l.isbn);
		fclose(pf);
	}
}
void eliminarLibro(ListaLibros *lL, int pos){
	int i;
	for (i=pos;i<lL->numL;i++){
		lL->aLibros[i] = lL->aLibros[i+1];
	}
	lL->numL--;
}
int buscarLibro(ListaLibros lL, char *titulo){
	int pos = 0, enc = 0;
	while(!enc && pos< lL.numL){
		if(strcmp(lL.aLibros[pos].titulo, titulo)==0){
			enc = 1;
		}
	}
	if(enc){
			return pos;
		}else{
			return -1;
		}
}

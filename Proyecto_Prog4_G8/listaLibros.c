#include "listaLibros.h"
#include<stdio.h>

void aniadirLibro(Libro l){
	FILE *pf;
	pf = fopen("Libros.txt","a");
	if(pf != (FILE*)NULL){
		fprintf("%s %s %s %d \n", l.titulo, l.autor, l.editorial, l.isbn);
		fclose(pf);
	}
}

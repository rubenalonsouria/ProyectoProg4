#include <stdio.h>
#include "libro.h"



Libro conseguirLibro(){
	Libro l;
	printf("Introduzca el titulo del libro: \n");
	fflush(stdout);
	fflush(stdin);
	gets(l.titulo);
	printf("Introduzca el isbn: \n");
	fflush(stdout);
	fflush(stdin);
	gets(l.isbn);
	printf("Introduzca la editorial: \n");
	fflush(stdout);
	fflush(stdin);
	gets(l.editorial);
	printf("Introduzca el autor: \n");
	fflush(stdout);
	fflush(stdin);
	gets(l.autor);
	return l;
}


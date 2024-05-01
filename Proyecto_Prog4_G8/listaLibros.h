#ifndef LISTALIBROS_H_
#define LISTALIBROS_H_
#include "libro.h"

typedef struct listaLibros{
	Libro *aLibros;
	int tam;
	int numL;
}ListaLibros;

void aniadirLibroaFichero(Libro l);
int buscarLibro(ListaLibros lL, char *titulo);
void eliminarLibro(ListaLibros *lL, int pos);

#endif /* LISTALIBROS_H_ */

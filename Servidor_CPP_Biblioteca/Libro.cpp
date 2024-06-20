#include "Libro.h"
#include <string.h>

Libro::Libro() {

}

Libro::Libro(const char* t,const char* a, const char* e, const char* i){
	strcpy(titulo,t);
	strcpy(autor,a);
	strcpy(editorial,e);
	strcpy(isbn,i);
}

const char* Libro::getTitulo() const{
	return titulo;
}

const char* Libro::getAutor() const{
	return autor;
}

const char* Libro::getEditorial() const{
	return editorial;
}

const char* Libro::getIsbn() const{
	return isbn;
}

void Libro::setLibro(const char* t, const char* a, const char* e, const char* i) {
	strcpy(titulo,t);
	strcpy(autor,a);
	strcpy(editorial,e);
	strcpy(isbn,i);
}
Libro::~Libro() {
	// TODO Auto-generated destructor stub
}


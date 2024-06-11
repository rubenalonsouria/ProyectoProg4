#include "Libro.h"

Libro::Libro() {

}

Libro::Libro(const char& t,const char& a, const char& e, const char& i)
: titulo(t), autor(a), editorial(e), isbn(i) {

}

const char& Libro::getTitulo() const{
	return titulo;
}

const char& Libro::getAutor() const{
	return autor;
}

const char& Libro::getEditorial() const{
	return editorial;
}

const char& Libro::getIsbn() const{
	return isbn;
}

void Libro::setLibro(const char& t, const char& a, const char& e, const char& i) {
    titulo = t;
    autor = a;
    editorial = e;
    isbn = i;
}
Libro::~Libro() {
	// TODO Auto-generated destructor stub
}


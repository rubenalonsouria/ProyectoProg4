#include "Libro.h"

Libro::Libro() {

}

Libro::Libro(const std::string& t,const std::string& a, const std::string& e, const std::string& i)
: titulo(t), autor(a), editorial(e), isbn(i) {

}

const std::string& Libro::getTitulo() const{
	return titulo;
}

const std::string& Libro::getAutor() const{
	return autor;
}

const std::string& Libro::getEditorial() const{
	return editorial;
}

const std::string& Libro::getIsbn() const{
	return isbn;
}
Libro::~Libro() {
	// TODO Auto-generated destructor stub
}


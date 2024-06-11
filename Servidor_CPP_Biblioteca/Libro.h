#ifndef LIBRO_H_
#define LIBRO_H_
#include <string>
class Libro {
	char titulo;
	char autor;
	char editorial;
	char isbn;
public:
	Libro();
	Libro(const char& t, const char& a, const char& e, const char& i);
	const char& getTitulo()const;
	const char& getAutor()const;
	const char& getEditorial()const;
	const char& getIsbn()const;
	void setLibro(const char& t, const char& a, const char& e, const char& i);
	virtual ~Libro();
};

#endif /* LIBRO_H_ */

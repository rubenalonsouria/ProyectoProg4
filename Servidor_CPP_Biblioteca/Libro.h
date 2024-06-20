#ifndef LIBRO_H_
#define LIBRO_H_
#include <string>
class Libro {
	char titulo[30];
	char autor[20];
	char editorial[20];
	char isbn[13];
public:
	Libro();
	Libro(const char* t, const char* a, const char* e, const char* i);
	const char* getTitulo()const;
	const char* getAutor()const;
	const char* getEditorial()const;
	const char* getIsbn()const;
	void setLibro(const char* t, const char* a, const char* e, const char* i);
	virtual ~Libro();
};

#endif /* LIBRO_H_ */

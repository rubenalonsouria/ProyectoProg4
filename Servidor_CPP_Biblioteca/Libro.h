#ifndef LIBRO_H_
#define LIBRO_H_
#include <string>
class Libro {
	std:: string titulo;
	std:: string autor;
	std:: string editorial;
	std:: string isbn;
public:
	Libro();
	Libro(const std::string& t, const std::string& a, const std::string& e, const std::string& i);
	const std:: string& getTitulo()const;
	const std:: string& getAutor()const;
	const std:: string& getEditorial()const;
	const std:: string& getIsbn()const;
	virtual ~Libro();
};

#endif /* LIBRO_H_ */

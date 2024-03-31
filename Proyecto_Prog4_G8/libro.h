#ifndef LIBRO_H_
#define LIBRO_H_
typedef struct libro{
	char titulo[30];
	char editorial[20];
	char autor[20];
	int isbn[13];
}Libro;

Libro conseguirLibro();


#endif /* LIBRO_H_ */

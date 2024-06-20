#ifndef ADMIN_H_
#define ADMIN_H_
#include <string>
class Admin {
	char nombre[20];
	char apellido[20];
	char dni[10];
	char numTarjeta[20];
	char contrasenya[20];
public:
	Admin();
	Admin(const char* n, const char* a, const char* d, const char* nt, const char* c);
	const char* getNombre()const;
	const char* getApellido()const;
	const char* getDni()const;
	const char* getNumTarjeta()const;
	const char* getContrasenya()const;
	virtual ~Admin();
};

#endif /* ADMIN_H_ */

/*
 * Usuario.h
 *
 *  Created on: 17 may 2024
 *      Author: Enrique
 */

#ifndef USUARIO_H_
#define USUARIO_H_

class Usuario {
	char nombre[20];
	char apellido[20];
	char dni[8];
	char numTarjeta[16];
	char contrasenya[20];
public:
	Usuario();
	Usuario(char *n, char *a, char*d,char *nT,char*c);
	char *getDni() const;
	char *getNombre() const;
	char *getApellido() const;
	char *getNumTarjeta() const;
	char *getContrasenya() const;
	virtual ~Usuario();
};

#endif /* USUARIO_H_ */

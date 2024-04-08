/*
 * admin.h
 *
 *  Created on: 8 abr 2024
 *      Author: ruby2
 */

#ifndef ADMIN_H_
#define ADMIN_H_

typedef struct admin{
	char nombre[20];
	char apellido[20];
	char dni[8];
	int numTarjeta[12];
	char contrasenya[20];
}Admin;

Admin conseguirAdmin();
void mostrarAdmin();
int contrasenyaCorrectaAdmin(char *conA, char *con);

#endif /* ADMIN_H_ */

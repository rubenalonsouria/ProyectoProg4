/*
 * Usuario.cpp
 *
 *  Created on: 17 may 2024
 *      Author: Enrique
 */

#include "Usuario.h"
#include <string.h>
Usuario::Usuario() {
	// TODO Auto-generated constructor stub

}

Usuario::Usuario(char *n, char *a, char*d,char* nT,char*c){
	strcpy(nombre,n);
	strcpy(apellido,a);
	strcpy(contrasenya,c);
	strcpy(numTarjeta,nT);
	strcpy(dni,d);
}

char *Usuario::getDni() const{
	return dni;
}
char *Usuario::getNombre() const{
	return nombre;
}
char *Usuario::getApellido() const{
	return  apellido;
}
char *Usuario::getNumTarjeta() const{
	return numTarjeta;
}
char *Usuario::getContrasenya() const{
	return contrasenya;
}
Usuario::~Usuario() {
	// TODO Auto-generated destructor stub
}


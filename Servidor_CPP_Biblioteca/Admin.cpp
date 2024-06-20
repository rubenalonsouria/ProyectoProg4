#include "Admin.h"
#include <string.h>

Admin::Admin() {

}

Admin::Admin(const char* n,const char* a, const char* d, const char* nt, const char* c){
	strcpy(nombre,n);
	strcpy(apellido,a);
	strcpy(dni,d);
	strcpy(numTarjeta,nt);
	strcpy(contrasenya,c);
}

const char* Admin::getNombre() const{
	return nombre;
}

const char* Admin::getApellido() const{
	return apellido;
}

const char* Admin::getDni() const{
	return dni;
}

const char* Admin::getNumTarjeta() const{
	return numTarjeta;
}

const char* Admin::getContrasenya() const{
	return contrasenya;
}

Admin::~Admin() {
	// TODO Auto-generated destructor stub
}


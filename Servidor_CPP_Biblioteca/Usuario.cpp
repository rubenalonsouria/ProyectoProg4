#include "Usuario.h"
#include <string.h>

Usuario::Usuario() {
    // Constructor predeterminado
}

Usuario::Usuario(const char *n, const char *a, const char *d, const char *nT, const char *c){
    // Constructor que inicializa los atributos con los valores proporcionados
	strcpy(nombre,n);
	strcpy(apellido,a);
	strcpy(dni,d);
	strcpy(numTarjeta,nT);
	strcpy(contrasenya,c);
}

const char* Usuario::getDni() const {
    return dni;
}

const char* Usuario::getNombre() const {
    return nombre;
}

const char* Usuario::getApellido() const {
    return apellido;
}

const char* Usuario::getNumTarjeta() const {
    return numTarjeta;
}

const char* Usuario::getContrasenya() const {
    return contrasenya;
}
void Usuario::setUsuario(const char *n,const char *a,const char *d,const char *nT,const char *c){
	strcpy(nombre,n);
	strcpy(apellido,a);
	strcpy(dni,d);
	strcpy(numTarjeta,nT);
	strcpy(contrasenya,c);
}
Usuario::~Usuario() {
    // Destructor
}

#include "Usuario.h"

Usuario::Usuario() {
    // Constructor predeterminado
}

Usuario::Usuario(const char n, const char a, const char d, const char nT, const char c)
    : nombre(n), apellido(a), dni(d), numTarjeta(nT), contrasenya(c) {
    // Constructor que inicializa los atributos con los valores proporcionados
}

char Usuario::getDni() const {
    return dni;
}

char Usuario::getNombre() const {
    return nombre;
}

char Usuario::getApellido() const {
    return apellido;
}

char Usuario::getNumTarjeta() const {
    return numTarjeta;
}

char Usuario::getContrasenya() const {
    return contrasenya;
}

void Usuario::setUsuario(const char n,const char a,const char d,const char nT,const char c){
	nombre = n;
	apellido = a;
	dni = d;
	numTarjeta = nT;
	contrasenya = c;
}
Usuario::~Usuario() {
    // Destructor
}

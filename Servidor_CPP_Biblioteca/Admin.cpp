#include "Admin.h"

Admin::Admin() {

}

Admin::Admin(const std::string& n,const std::string& a, const std::string& d, const std::string& nt, const std::string& c)
: nombre(n), apellido(a), dni(d), numTarjeta(nt), contrasenya(c) {

}

const std::string& Admin::getNombre() const{
	return nombre;
}

const std::string& Admin::getApellido() const{
	return apellido;
}

const std::string& Admin::getDni() const{
	return dni;
}

const std::string& Admin::getNumTarjeta() const{
	return numTarjeta;
}

const std::string& Admin::getContrasenya() const{
	return contrasenya;
}

Admin::~Admin() {
	// TODO Auto-generated destructor stub
}


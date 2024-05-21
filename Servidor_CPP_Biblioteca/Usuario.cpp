#include "Usuario.h"

Usuario::Usuario() {
    // Constructor predeterminado
}

Usuario::Usuario(const std::string& n, const std::string& a, const std::string& d, const std::string& nT, const std::string& c)
    : nombre(n), apellido(a), dni(d), numTarjeta(nT), contrasenya(c) {
    // Constructor que inicializa los atributos con los valores proporcionados
}

const std::string& Usuario::getDni() const {
    return dni;
}

const std::string& Usuario::getNombre() const {
    return nombre;
}

const std::string& Usuario::getApellido() const {
    return apellido;
}

const std::string& Usuario::getNumTarjeta() const {
    return numTarjeta;
}

const std::string& Usuario::getContrasenya() const {
    return contrasenya;
}

Usuario::~Usuario() {
    // Destructor
}

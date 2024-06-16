#ifndef USUARIO_H_
#define USUARIO_H_

#include <string> // Incluir la biblioteca de std::string

class Usuario {
    char nombre;
    char apellido;
    char dni;
    char numTarjeta;
    char contrasenya;
public:
    Usuario();
    Usuario(const char n, const char a, const char d, const char nT, const char c);
    char getDni() const;
    char getNombre() const;
    char getApellido() const;
    char getNumTarjeta() const;
    char getContrasenya() const;
    void setUsuario(const char nombre,const char apellido,const char dni,const char numTarjeta,const char contrasenya);
    virtual ~Usuario();
};

#endif /* USUARIO_H_ */

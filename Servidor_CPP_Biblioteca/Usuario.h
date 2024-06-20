#ifndef USUARIO_H_
#define USUARIO_H_

#include <string> // Incluir la biblioteca de std::string

class Usuario {
    char nombre[20];
    char apellido[20];
    char dni[10];
    char numTarjeta[16];
    char contrasenya[20];
public:
    Usuario();
    Usuario(const char *n, const char *a, const char *d, const char *nT, const char *c);
    const char * getDni() const;
    const char * getNombre() const;
    const char * getApellido() const;
    const char * getNumTarjeta() const;
    const char * getContrasenya() const;
    void setUsuario(const char *nombre,const char *apellido,const char *dni,const char *numTarjeta,const char *contrasenya);
    virtual ~Usuario();
};

#endif /* USUARIO_H_ */

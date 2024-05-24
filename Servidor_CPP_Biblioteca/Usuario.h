#ifndef USUARIO_H_
#define USUARIO_H_

#include <string> // Incluir la biblioteca de std::string

class Usuario {
    std::string nombre;
    std::string apellido;
    std::string dni;
    std::string numTarjeta;
    std::string contrasenya;
public:
    Usuario();
    Usuario(const std::string& n, const std::string& a, const std::string& d, const std::string& nT, const std::string& c);
    const std::string& getDni() const;
    const std::string& getNombre() const;
    const std::string& getApellido() const;
    const std::string& getNumTarjeta() const;
    const std::string& getContrasenya() const;
    void setUsuario(const std::string& nombre,const std::string& apellido,const std::string& dni,const std::string& numTarjeta,const std::string& contrasenya);
    virtual ~Usuario();
};

#endif /* USUARIO_H_ */

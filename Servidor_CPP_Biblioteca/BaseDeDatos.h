#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

#include "sqlite3.h"
#include "Usuario.h"
#include "Libro.h"
#include <string>

class BaseDeDatos {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *nomBD;

public:
    BaseDeDatos(const char *nomBD);
    void conectar();
    void desconectar();
    void crearTablas();
    void insertarUsuario(const Usuario &u);
    int buscarUsuario(const char *nombre);
    int buscarDni(const char *dni);   // Añadir declaración
    std::string getContrasenya(const char *dni);  // Añadir declaración
    void insertarLibro(const Libro &l);
    int buscarLibro(const char *isbn);
    int contrasenyaCorrecta(const std::string& nombre, const std::string& contrasenya);
    void eliminarLibro(const Libro& l);
    int contrasenyaAdminCorrecta(const std::string& nombre, const std::string& contrasenya);
    int buscarAdmin(const char *nombre);
    void actualizarContrasenyaUsuario(const std::string& dni, const std::string& nuevaContrasenya);
    void eliminarUsuario(const std::string& nombre);
    virtual ~BaseDeDatos();
};

#endif /* BASEDEDATOS_H_ */

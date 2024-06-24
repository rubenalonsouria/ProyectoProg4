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
    Usuario* obtenerUsuario(const char *dni);
    int buscarDni(const char *dni);   // Añadir declaración
    char* getContrasenya(const char *dni);  // Añadir declaración
    void insertarLibro(const Libro &l);
    int buscarLibro(const char *isbn);
    int contrasenyaCorrecta(const char *dni, const char *contrasenya);
    void eliminarLibro(const Libro& l);
    int contrasenyaAdminCorrecta(const char *nombre, const char *contrasenya);
    int buscarAdmin(const char *nombre);
    void actualizarContrasenyaUsuario(const char *dni, const char *nuevaContrasenya);
    void eliminarUsuario(const char *nombre);
    virtual ~BaseDeDatos();
};

#endif /* BASEDEDATOS_H_ */

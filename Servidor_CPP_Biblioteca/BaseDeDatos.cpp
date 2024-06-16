#include "BaseDeDatos.h"
#include <string.h>
#include <iostream>

using namespace std;

BaseDeDatos::BaseDeDatos(const char *nomBD) {
    this->nomBD = new char[strlen(nomBD) + 1];
    strcpy(this->nomBD, nomBD);
    db = NULL;
    stmt = NULL;
}

void BaseDeDatos::conectar() {
    int result = sqlite3_open(nomBD, &db);
    if (result != SQLITE_OK) {
        cout << "Error al abrir la BBDD\n";
    }
}

void BaseDeDatos::desconectar() {
    sqlite3_close(db);
}

void BaseDeDatos::crearTablas() {
    char sql[200];
    sprintf(sql, "CREATE TABLE IF NOT EXISTS Usuario ("
                 "dni VARCHAR(10), "
                 "nombre VARCHAR(20), "
                 "apellido VARCHAR(20), "
                 "numTarjeta VARCHAR(16), "
                 "contrasenya VARCHAR(20));");

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    sprintf(sql, "CREATE TABLE IF NOT EXISTS Libro ("
                 "titulo VARCHAR(30), "
                 "editorial VARCHAR(20), "
                 "autor VARCHAR(20), "
                 "isbn VARCHAR(13));");

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    sprintf(sql, "CREATE TABLE IF NOT EXISTS Admin ("
                 "dni VARCHAR(10), "
                 "nombre VARCHAR(20), "
                 "apellido VARCHAR(20), "
                 "numTarjeta VARCHAR(16),"
                 "contrasenya VARCHAR(16));");

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void BaseDeDatos::insertarUsuario(const Usuario &u) {
    char sql[200];
    sprintf(sql, "INSERT INTO Usuario (dni, nombre, apellido, numTarjeta, contrasenya) VALUES "
                 "('%s', '%s', '%s', '%s', '%s');",
                 u.getDni(), u.getNombre(), u.getApellido(), u.getNumTarjeta(), u.getContrasenya());
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

int BaseDeDatos::buscarUsuario(const char *dni) {
    int resultado;
    char sql[200];
    sprintf(sql, "SELECT * FROM Usuario WHERE dni='%s';", dni);
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    int result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        resultado = 1;
    } else {
        resultado = -1;
    }
    sqlite3_finalize(stmt);
    return resultado;
}

Usuario* BaseDeDatos::obtenerUsuario(const char *dni){
	int resultado;
	char sql[200];
	sprintf(sql, "SELECT * FROM Usuario WHERE dni='%s';", dni);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	int result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		char *nom = (char*)sqlite3_column_text(stmt,1);
		char *ape = (char*)sqlite3_column_text(stmt,2);
		char *numT = (char*)sqlite3_column_text(stmt,3);
		char *cont = (char*)sqlite3_column_text(stmt,4);
		Usuario *u = new Usuario(dni,nom,ape,numT,cont);
		sqlite3_finalize(stmt);

		return u;
	}else{
		return NULL;
	}

}



int BaseDeDatos::buscarDni(const char *dni) {
    int resultado;
    char sql[200];
    sprintf(sql, "SELECT * FROM Usuario WHERE dni='%s';", dni);
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    int result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        resultado = 1;
    } else {
        resultado = -1;
    }
    sqlite3_finalize(stmt);
    return resultado;
}

char BaseDeDatos::getContrasenya(const char *dni) {
    char contrasenya;
    char sql[200];
    sprintf(sql, "SELECT contrasenya FROM Usuario WHERE dni='%s';", dni);
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *dbContrasenya = sqlite3_column_text(stmt, 0);
        contrasenya = reinterpret_cast<const char*>(dbContrasenya);
    } else {
        contrasenya = "No encontrada";
    }
    sqlite3_finalize(stmt);
    return contrasenya;
}

void BaseDeDatos::insertarLibro(const Libro &l) {
    char sql[200];
    sprintf(sql, "INSERT INTO Libro (titulo, editorial, autor, isbn) VALUES "
                 "('%s', '%s', '%s', '%s');",
                 l.getTitulo(), l.getEditorial(), l.getAutor(), l.getIsbn());
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

int BaseDeDatos::buscarLibro(const char *isbn) {
    int resultado;
    char sql[200];
    sprintf(sql, "SELECT * FROM Libro WHERE isbn='%s';", isbn);
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    int result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        resultado = 1;
    } else {
        resultado = -1;
    }
    sqlite3_finalize(stmt);
    return resultado;
}

int BaseDeDatos::contrasenyaCorrecta(const char nombre, const char contrasenya) {
    char sql[256];
    int correcta = 0;
    sprintf(sql, "SELECT contrasenya FROM Usuario WHERE nombre='%s';");
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Error preparando el statement: " << sqlite3_errmsg(db) << std::endl;
        return 0;
    }
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *dbContrasenya = sqlite3_column_text(stmt, 0);
        if (dbContrasenya && contrasenya == reinterpret_cast<const char*>(dbContrasenya)) {
            correcta = 1;
        }
    } else {
        std::cerr << "Error ejecutando el statement o usuario no encontrado: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
    return correcta;
}

void BaseDeDatos::eliminarLibro(const Libro& l) {
    char sql[256];
    sprintf(sql, "DELETE FROM Libro WHERE isbn='%s';");
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Error preparando el statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error ejecutando el statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

int BaseDeDatos::contrasenyaAdminCorrecta(const char nombre, const char contrasenya) {
    char sql[256];
    int correcta = 0;
    sprintf(sql, "SELECT contrasenya FROM Admin WHERE nombre='%s';");
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Error preparando el statement: " << sqlite3_errmsg(db) << std::endl;
        return 0;
    }
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *dbContrasenya = sqlite3_column_text(stmt, 0);
        if (dbContrasenya && contrasenya == reinterpret_cast<const char*>(dbContrasenya)) {
            correcta = 1;
        }
    } else {
        std::cerr << "Error ejecutando el statement o administrador no encontrado: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
    return correcta;
}

int BaseDeDatos::buscarAdmin(const char *nombre) {
    int resultado;
    char sql[200];
    sprintf(sql, "SELECT * FROM Admin WHERE nombre='%s';", nombre);
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    int result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        resultado = 1;
    } else {
        resultado = -1;
    }
    sqlite3_finalize(stmt);
    return resultado;
}

void BaseDeDatos::actualizarContrasenyaUsuario(const char dni, const char nuevaContrasenya) {
    char sql[256];
    sprintf(sql, "UPDATE Usuario SET contrasenya='%s' WHERE dni='%s';");
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Error preparando el statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error ejecutando el statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void BaseDeDatos::eliminarUsuario(const char dni) {
    char sql[256];
    sprintf(sql, "DELETE FROM Usuario WHERE dni='%s';");
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Error preparando el statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error ejecutando el statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

BaseDeDatos::~BaseDeDatos() {
    delete[] nomBD;
}


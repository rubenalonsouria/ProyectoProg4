/*
 * BaseDeDatos.h
 *
 *  Created on: 17 may 2024
 *      Author: Enrique
 */

#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_
#include "sqlite3.h"
#include "Usuario.h"
class BaseDeDatos {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	char *nomBD;

public:
	BaseDeDatos(const char *nomBD);
	void conectar();
	void desconectar();
	void crearTablas();
	void insertarUsuario(const Usuario&u);
	int buscarUsuario(const char *nombre);
	virtual ~BaseDeDatos();
};

#endif /* BASEDEDATOS_H_ */

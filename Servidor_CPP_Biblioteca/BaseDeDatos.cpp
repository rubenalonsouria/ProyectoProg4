/*
 * BaseDeDatos.cpp
 *
 *  Created on: 17 may 2024
 *      Author: Enrique
 */

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
	sprintf(sql,
			"create table if not exists Usuario(dni varchar2(10), nom varchar2(20), apellido varchar2(20)), numTarjeta varchar(16), constrasenya varchar2(20)");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //Preparar la sentencia
	sqlite3_step(stmt); //Ejecutar la sentencia
	sqlite3_finalize(stmt); //Cerrar la sentencia

}

void BaseDeDatos::insertarUsuario(const Usuario &u) {
	char sql[200];

	sprintf(sql, "insert into Usuario values('%s','%s','%s','%s','%s')",
			u.getDni(), u.getNombre(), u.getApellido(), u.getNumTarjeta(),
			u.getContrasenya());
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //Preparar la sentencia
	sqlite3_step(stmt); //Ejecutar la sentencia
	sqlite3_finalize(stmt); //Cerrar la sentencia

}

int buscarUsuario(const char *nombre) {
	int resultado;
	char sql[200];
	sprintf(sql, "select * from Usuario where nombre='%s'",nombre);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //Preparar la sentencia
	int result = sqlite3_step(stmt); //Ejecutar la sentencia
	if (result == SQLITE_ROW) { //Mientras haya tuplas/filas que mirar
		resultado = 1;
	}else{
		resultado = -1;
	}
	sqlite3_finalize (stmt); //Cerrar la sentencia
	return resultado;

}
BaseDeDatos::~BaseDeDatos() {
	delete[] nomBD;
}


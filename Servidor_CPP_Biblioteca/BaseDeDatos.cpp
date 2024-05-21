/*
 * BaseDeDatos.cpp
 *
 *  Created on: 21 may 2024
 *      Author: PORTATIL
 */

#include "BaseDeDatos.h"
#include <string.h>
#include <iostream>

using namespace std; // @suppress("Symbol is not resolved")

BaseDeDatos::BaseDeDatos(const char *nomBD) {
    this->nomBD = new char[strlen(nomBD) + 1]; // @suppress("Function cannot be resolved")
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
}

void BaseDeDatos::insertarUsuario(const Usuario &u) {
    char sql[200];
    sprintf(sql, "INSERT INTO Usuario (dni, nombre, apellido, numTarjeta, contrasenya) VALUES "
                 "('%s', '%s', '%s', '%s', '%s')",
                 u.getDni(), u.getNombre(), u.getApellido(), u.getNumTarjeta(), u.getContrasenya());
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

int BaseDeDatos::buscarUsuario(const char *nombre) {
    int resultado;
    char sql[200];
    sprintf(sql, "SELECT * FROM Usuario WHERE nombre='%s'", nombre);
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

BaseDeDatos::~BaseDeDatos() {
    delete[] nomBD;
}




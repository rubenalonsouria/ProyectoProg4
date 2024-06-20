#include <stdio.h>
#include <winsock2.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include "BaseDeDatos.h"
#include "Usuario.h"
#include "Libro.h"

using namespace std;

#define NOMFICH "Configuracion.txt"

void leerFicheroConfig(const char *nomfich, char *nombre_bd, char *server_ip, int *server_port) {
    ifstream ifs(nomfich);
    char linea[200];
    ifs >> linea;
    strtok(linea, "=");
    sprintf(nombre_bd, strtok(NULL, ""));
    ifs >> linea;
    strtok(linea, "=");
    sprintf(server_ip, strtok(NULL, ""));
    ifs >> linea;
    strtok(linea, "=");
    *server_port = atoi(strtok(NULL, ""));
}

void manejarCliente(SOCKET comm_socket, BaseDeDatos &bd) {
    char sendBuff[512], recvBuff[512];
    char opcion, opcionU, opcionA;
    char nombre[20], contrasenya[20], dni[8], numTarjeta[16], apellido[20];
    char titulo[30], editorial[20], autor[20], isbn[13];
    int pos, esCorrecta;
    Libro l;
    Usuario u;

    do {
        memset(recvBuff, 0, sizeof(recvBuff));
        recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
        sscanf(recvBuff, "%c", &opcion);

        switch (opcion) {
            case '1':
                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                sscanf(recvBuff, "%s", nombre);
                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                sscanf(recvBuff, "%s", contrasenya);

                pos = bd.buscarUsuario(nombre);
                esCorrecta = bd.contrasenyaCorrecta(nombre, contrasenya);

                if (pos == -1) {
                    sprintf(sendBuff, "No existe este registro\n");
                } else if (esCorrecta) {
                    sprintf(sendBuff, "Bienvenido\n");
                    send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                    do {
                        memset(recvBuff, 0, sizeof(recvBuff));
                        recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                        sscanf(recvBuff, "%c", &opcionU);
                        switch (opcionU) {
                            case '1':
                                // Añadir libro
                                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                sscanf(recvBuff, "%s", titulo);
                                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                sscanf(recvBuff, "%s", editorial);
                                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                sscanf(recvBuff, "%s", autor);
                                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                sscanf(recvBuff, "%s", isbn);
                                l.setLibro(titulo, editorial, autor, isbn);
                                bd.insertarLibro(l);
                                sprintf(sendBuff, "Libro añadido\n");
                                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                                break;
                            case '2':
                                // Devolver libro
                                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                sscanf(recvBuff, "%s", isbn);
                                pos = bd.buscarLibro(isbn);
                                if (pos == -1) {
                                    sprintf(sendBuff, "No existe ese libro\n");
                                } else {
                                    l.setLibro(titulo, editorial, autor, isbn);
                                    bd.eliminarLibro(l);
                                    sprintf(sendBuff, "Libro devuelto\n");
                                }
                                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                                break;
                            case '3':
                                // Consultar libro
                                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                sscanf(recvBuff, "%s", isbn);
                                pos = bd.buscarLibro(isbn);
                                if (pos == -1) {
                                    sprintf(sendBuff, "No existe ese libro\n");
                                } else {
                                    sprintf(sendBuff, "Libro disponible\n");
                                }
                                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                                break;
                            case '4':
                                break;
                        }
                    } while (opcionU != '0');
                } else {
                    sprintf(sendBuff, "Contraseña incorrecta\n");
                }
                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                break;

            case '2':
                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                sscanf(recvBuff, "%s", nombre);
                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                sscanf(recvBuff, "%s", contrasenya);

                pos = bd.buscarAdmin(nombre);
                esCorrecta = bd.contrasenyaAdminCorrecta(nombre, contrasenya);

                if (pos == -1) {
                    sprintf(sendBuff, "No existe este registro");
                } else if (esCorrecta) {
                    sprintf(sendBuff, "Bienvenido\n");
                    send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                    do {
                        memset(recvBuff, 0, sizeof(recvBuff));
                        recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                        sscanf(recvBuff, "%c", &opcionA);
                        switch (opcionA) {
                            case '4':
                                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                sprintf(dni, "%s", recvBuff);
                                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                sprintf(nombre, "%s", recvBuff);
                                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                sprintf(apellido, "%s", recvBuff );
                                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                sprintf(numTarjeta, "%s", recvBuff );
                                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                sprintf(contrasenya, "%s", recvBuff );
                                u.setUsuario(nombre, apellido, dni, numTarjeta, contrasenya);
                                pos = bd.buscarUsuario(nombre);
                                if (pos != -1) {
                                    sprintf(sendBuff, "Ese nombre de usuario ya existe\n");
                                } else {
                                    bd.insertarUsuario(u);
                                    sprintf(sendBuff, "Usuario registrado correctamente\n");
                                }
                                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                                break;

                            case '5':
                                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                sprintf(dni, "%s", recvBuff);
                                bd.eliminarUsuario(dni);
                                sprintf(sendBuff, "Usuario eliminado\n");
                                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                                break;
                            case '6':
                            	char d[10];
                            	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                            	sprintf(d, "%s", recvBuff);
                            	pos = bd.buscarUsuario(d);
                            	if(pos==-1){
                            		sprintf(sendBuff,"Usuario no encontrado\n");
                            	}else{
                            		Usuario *u = bd.obtenerUsuario(d);
                            		sprintf(sendBuff,"%s",u->getDni());
                            		send(comm_socket,sendBuff,sizeof(sendBuff),0);
                            		sprintf(sendBuff,"%s",u->getNombre());
                            		send(comm_socket,sendBuff,sizeof(sendBuff),0);
                            		sprintf(sendBuff,"%s",u->getApellido());
                            		send(comm_socket,sendBuff,sizeof(sendBuff),0);
                            		sprintf(sendBuff,"%s",u->getNumTarjeta());
                            		send(comm_socket,sendBuff,sizeof(sendBuff),0);
                            		sprintf(sendBuff,"%s",u->getContrasenya());
                            		send(comm_socket,sendBuff,sizeof(sendBuff),0);
                            	}
                            default:
                                sprintf(sendBuff, "Opción incorrecta\n");
                                send(comm_socket, sendBuff, sizeof(sendBuff), 0);

                                break;
                        }
                    } while (opcionA != '0');
                } else {
                    sprintf(sendBuff, "Contraseña incorrecta\n");
                }
                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                break;

            case '3':
                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                sprintf(dni, "%s", recvBuff);
                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                sprintf(nombre, "%s", recvBuff);
                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                sprintf(apellido, "%s", recvBuff);
                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                sprintf(numTarjeta, "%s", recvBuff);
                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                sprintf(contrasenya, "%s", recvBuff);

                u.setUsuario(nombre, apellido, dni, numTarjeta, contrasenya);
                pos = bd.buscarUsuario(nombre);
                if (pos != -1) {
                    sprintf(sendBuff, "Ese nombre de usuario ya existe\n");
                } else {
                    bd.insertarUsuario(u);
                    sprintf(sendBuff, "Usuario registrado correctamente\n");
                }
                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                break;

            case '4':
                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                sscanf(recvBuff, "%s", dni);
                pos = bd.buscarDni(dni);
                if (pos == -1) {
                    sprintf(sendBuff, "No existe este registro\n");
                } else {
                    sprintf(sendBuff, "Su contraseña es: %s\n", bd.getContrasenya(dni));
                }
                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                break;

            default:
                sprintf(sendBuff, "Opción incorrecta\n");
                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                break;
        }
    } while (opcion != '0');

    closesocket(comm_socket);
}

int main() {
    WSADATA wsaData;
    SOCKET listening_socket, comm_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len;
    char nombre_bd[50], server_ip[16];
    int server_port;

    leerFicheroConfig(NOMFICH, nombre_bd, server_ip, &server_port);

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    listening_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    bind(listening_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(listening_socket, 5);

    BaseDeDatos bd(nombre_bd);
    bd.conectar();
    bd.crearTablas();

    while (1) {
        client_addr_len = sizeof(client_addr);
        comm_socket = accept(listening_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        manejarCliente(comm_socket, bd);
    }

    bd.desconectar();
    closesocket(listening_socket);
    WSACleanup();

    return 0;
}

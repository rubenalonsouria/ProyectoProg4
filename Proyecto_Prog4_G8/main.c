#include <stdio.h>
#include <stdlib.h>
#include "listaUsuarios.h"
#include "menus.h"
#include "listaLibros.h"
#include "listaAdmin.h"
#include <winsock2.h>

#define NOMFICH1 "Usuarios.txt"
#define NOMFICH2 "Admin.txt"
#define NOMFICH3 "Libros.txt"
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int main() {
	//ListaUsuarios lu;
	//ListaLibros lL;
	Usuario u;
	int tam, pos;
	char opcion, opcionU, dni[8], titulo;
	Libro l;

	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));

	//lu.numU = 0;
	//lu.aUsuarios = NULL;
	//volcarFicheroAListaUsuarios(&lu, NOMFICH1);

	//ListaAdmin la;
	Admin a;
	int posA;
	char opcionAd, opcionA;

	//la.numA = 0;
	//la.aAdmin = NULL;
	//volcarFicheroAListaAdmin(&la, NOMFICH2);

do {
	opcion = menuPrincipal();
	sprintf(sendBuff,"%c",opcion);
	send(s,sendBuff,sizeof(sendBuff),0);
	switch (opcion) {
		case '0':
		printf("Cerrando programa, hasta pronto\n");
		fflush(stdout);
		break;
		case '1':
		u = conseguirUsuario();
		sprintf(sendBuff,"%s",u.nombre);
		send(s,sendBuff,sizeof(sendBuff),0);
		sprintf(sendBuff,"%s",u.contrasenya);
		send(s,sendBuff,sizeof(sendBuff),0);

		recv(s,recvBuff,sizeof(recvBuff),0);
		if(strcmp(recvBuff,"No existe este registro\n")==0) {
			printf("%s",recvBuff);
		} else {
			printf("%s",recvBuff);
			do {
				opcionU = menuUsuario();
				sprintf(sendBuff,"%c",opcionU);
				send(s,sendBuff,sizeof(sendBuff),0);

				switch (opcionU) {
					case '0':
					printf("Volviendo al menu principal\n");
					fflush(stdout);
					break;
					case '1':
					l = conseguirLibro();
					sprintf(sendBuff,"%s",l.titulo);
					send(s,sendBuff,sizeof(sendBuff),0);
					sprintf(sendBuff,"%s",l.editorial);
					send(s,sendBuff,sizeof(sendBuff),0);
					sprintf(sendBuff,"%s",l.autor);
					send(s,sendBuff,sizeof(sendBuff),0);
					sprintf(sendBuff,"%s",l.isbn);
					send(s,sendBuff,sizeof(sendBuff),0);
					//aniadirLibroaFichero(l);  Esto al servidor
					break;
					case '2':
					printf(
							"Introduzca el titulo del libro a devolver\n");
					fflush(stdout);
					fflush(stdin);
					scanf(l.titulo);
					sprintf(sendBuff,"%s",l.titulo);
					send(s,sendBuff,sizeof(sendBuff),0);
					recv(s,recvBuff,sizeof(recvBuff),0);
					printf("%s\n",recvBuff);

					break;
					case '3':
					printf("Pago de la multa: \n");
					break;
					case '4':
					printf("Introduce el titulo a buscar \n");
					fflush(stdout);
					fflush(stdin);
					scanf(l.titulo);

					break;
					default:
					printf("La opcion seleccionada no es correcta\n");
				}
			}while (opcionU != '0');
			printf("La contraseña no es correcta\n");
			fflush(stdout);
		}

		break;

		case '2':
		a = conseguirAdmin();
		sprintf(sendBuff,"%s",a.nombre);
		send(s,sendBuff,sizeof(sendBuff),0);
		sprintf(sendBuff,"%s",a.contrasenya);
		send(s,sendBuff,sizeof(sendBuff),0);

		recv(s,recvBuff,sizeof(recvBuff),0);
		//posA = buscarAdmin(la, a.nombre);
		if (strncmp(recvBuff,"No existe este registro",23)==0) {
			printf("%s\n",recvBuff);
		} else {
			if (strncmp(recvBuff,"Bienvenido",10)==0) {
				printf("%s\n",recvBuff);
				fflush(stdout);
				do {
					opcionA = menuAdmin();
					sprintf(sendBuff,"%c",opcionA);
					send(s,sendBuff,sizeof(sendBuff),0);

					switch (opcionA) {
						case '0':
						printf("Volviendo al menu principal\n");
						fflush(stdout);
						break;
						case '1':
						l = conseguirLibro();
						aniadirLibroaFichero(l);
						break;
						case '2':
						break;
						case '3':
						break;
						case '4':
						u = conseguirUsuario();
						//aniadirUsuario(&lu, u);
						sprintf(sendBuff,"%s",u.dni);
						send(s,sendBuff,sizeof(sendBuff),0);
						sprintf(sendBuff,"%s",u.nombre);
						send(s,sendBuff,sizeof(sendBuff),0);
						sprintf(sendBuff,"%s",u.apellido);
						send(s,sendBuff,sizeof(sendBuff),0);
						sprintf(sendBuff,"%s",u.numTarjeta);
						send(s,sendBuff,sizeof(sendBuff),0);
						sprintf(sendBuff,"%s",u.contrasenya);
						send(s,sendBuff,sizeof(sendBuff),0);
						recv(s,recvBuff,sizeof(recvBuff),0);
						printf("%s\n",recvBuff);
						break;
						case '5':
						printf("Introduce el dni del usuario a eliminar: ");
						fflush(stdout);
						fflush(stdin);
						gets(u.dni);
						//pos = buscarUsuario(lu, u.dni);
						sprintf(sendBuff,"%s",u.dni);
						send(s,sendBuff,sizeof(sendBuff),0);
						recv(s,recvBuff,sizeof(recvBuff),0);
						printf("%s\n",recvBuff);

						break;
						case '6':
						printf(
								"Introduce el dni del usuario que deseas buscar: ");
						fflush(stdout);
						fflush(stdin);
						gets(u.dni);
						sprintf(sendBuff,"%s",u.dni);
						send(s,sendBuff,sizeof(sendBuff),0);

						recv(s,recvBuff,sizeof(recvBuff),0);
						if(strncmp(recvBuff,"Usuario no encontrado",21)==0){
							printf("%s\n",recvBuff);
						}else{
							sprintf(dni,"%s",recvBuff);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sprintf(u.nombre,"%s",recvBuff);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sprintf(u.apellido,"%s",recvBuff);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sprintf(u.numTarjeta,"%s",recvBuff);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sprintf(u.contrasenya,"%s",recvBuff);
							printf("%s %s %s %s %s\n",u.dni,u.nombre,u.apellido,u.numTarjeta,u.contrasenya);
						}
						break;
						default:
						printf("La opcion seleccionada no es correcta\n");
					}
				}while (opcionA != '0');
			} else {
				printf("La contraseña no es correcta\n");
				fflush(stdout);
			}
		}
		break;

		case '3':
			u = conseguirUsuario();
			sprintf(sendBuff,"%s",u.dni);
			send(s,sendBuff,sizeof(sendBuff),0);

			sprintf(sendBuff,"%s",u.nombre);
			send(s,sendBuff,sizeof(sendBuff),0);

			sprintf(sendBuff,"%s",u.apellido);
			send(s,sendBuff,sizeof(sendBuff),0);
			sprintf(sendBuff,"%s",u.numTarjeta);
			send(s,sendBuff,sizeof(sendBuff),0);

			sprintf(sendBuff,"%s",u.contrasenya);
			send(s,sendBuff,sizeof(sendBuff),0);

			recv(s,recvBuff,sizeof(recvBuff),0);
			printf("%s",recvBuff);

			break;
			default:
			printf("La opcion seleccionada no es correcta\n");
			fflush(stdout);
		}
	}while (opcion != '0');
	//free(lu.aUsuarios);

	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();
}

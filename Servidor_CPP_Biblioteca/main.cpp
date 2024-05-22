// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>
#include "BaseDeDatos.h"
#include "Usuario.h"
#include "Libro.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n");

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	//SEND and RECEIVE data
	printf("Waiting for incoming messages from client... \n");
	BaseDeDatos bd("LibreriaDeusto.db");
	bd.conectar();
	char opcion, opcionU, nombre[20], contrasenya[20],dni[8],numTarjeta[16],apellido[20];
	char titulo[30];
	char editorial[20];
	char autor[20];
	char isbn[13];
	int pos;
	do {
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		sscanf(recvBuff, "%c", &opcion);
		switch (opcion) {
		case '1':
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			sprintf(nombre, "%s", recvBuff);
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			sprintf(contrasenya, "%s", recvBuff);
			//pos = buscarUsuario(lu, nombre);
			pos = bd.buscarUsuario(nombre);
			if (pos == -1) {
				sprintf(sendBuff, "No existe este registro\n");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			} else {
				if (contrasenyaCorrecta(lu.aUsuarios[pos].contrasenya,
						contrasenya)) {
					sprintf(sendBuff, "Bienvenido\n");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					do {
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
						sscanf(recvBuff, "%c", &opcionU);
						switch (opcionU) {
						case '1':
							recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
							sprintf(titulo, "%s", recvBuff);
							recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
							sprintf(editorial, "%s", recvBuff);
							recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
							sprintf(autor, "%s", recvBuff);
							recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
							sprintf(isbn, "%s", recvBuff);
							Libro l(titulo, editorial, autor, isbn);
							aniadirLibroaFichero(l);         //Mejor añadir a la bbdd
							break;
						case '2':
							recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
							sprintf(titulo, "%s", recvBuff);
							pos = buscarLibro(lL, titulo);
							if (pos == -1) {
								sprintf(sendBuff,"No existe ese libro\n");
								send(comm_socket, sendBuff, sizeof(sendBuff), 0);

							} else {
								eliminarLibro(&lL, pos);
								sprintf(sendBuff,"Libro devuelto\n");
								send(comm_socket, sendBuff, sizeof(sendBuff), 0);

							}
							break;
						case '3':
							break;
						case '4':
							sprintf(sendBuff,"%s",titulo);
							send(s,sendBuff,sizeof(sendBuff),0);
							pos = buscarLibro(lL, titulo);

							break;
						}

					} while (opcionU != '0');
				}
			}
			break;
		case '2':
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
			Usuario usu(dni,nombre,apellido,numTarjeta,contrasenya);

			//pos = buscarUsuario(lu, nombre);
			pos = bd.buscarUsuario(nombre);
			if(pos!=-1){
				sprintf(sendBuff,"Ese nombre de usuario ya existe\n");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}else{
				sprintf(sendBuff,"Se ha registrado correctamente el usuario \n");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				aniadirUsuario(&lu, usu);
				bd.insertarUsuario(usu);
				aniadirUsuarioAlFinalDelFichero(usu, NOMFICH1);
			}
			break;
		}

	} while (opcion != '0');
	bd.desconectar();
	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}

/*
 * int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
 if (bytes > 0) {
 printf("Receiving message... \n");
 printf("Data received: %s \n", recvBuff);

 printf("Sending reply... \n");
 strcpy(sendBuff, "ACK -> ");
 strcat(sendBuff, recvBuff);
 send(comm_socket, sendBuff, sizeof(sendBuff), 0);
 printf("Data sent: %s \n", sendBuff);

 if (strcmp(recvBuff, "Bye") == 0)
 break;
 }
 *
 * */

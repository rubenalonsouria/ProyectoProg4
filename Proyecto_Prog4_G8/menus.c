#include "menus.h"
#include <stdio.h>

char menuPrincipal(){
	char opcion;
	printf("1) Inicio de Sesión: \n");
	printf("2) Registrarse: \n");
	printf("3) Has olvidado tu contraseña: \n");
	printf("0) Salir \n");
	printf("Elige una opcion: \n");
	fflush(stdout);
	fflush(stdin);
	scanf("%c", &opcion);
	return opcion;
}
char menuUsuario(){
	char opcion;
	printf("1) Reservar libro\n");
	printf("2) Devolver libro\n");
	printf("3) Pagar multa\n");
	printf("4) Buscar libro\n");
	printf("0) Salir\n");
	printf("Elige una opcion\n");
	fflush(stdout);
	fflush(stdin);
	scanf("%c", &opcion);
	return opcion;
}




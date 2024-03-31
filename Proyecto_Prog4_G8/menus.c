#include "menus.h"
#include <stdio.h>

char menuPrincipal(){
	char opcion;
	printf("1) Inicio de Sesión: \n");
	printf("2) Registrarse: /n");
	printf("3) Has olvidado tu contrasña: /n");
	printf("0) Salir /n");
	printf("Elige una opcion: /n");
	fflush(stdout);
	fflush(stdin);
	scanf("%c", opcion);
	return opcion;
}




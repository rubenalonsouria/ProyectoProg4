#include "usuario.h"

#include <stdio.h>
#include <string.h>

Usuario conseguirUsuario(){
	Usuario u;
	printf("Introduce el nombre: /n");
	fflush(stdout);
	fflush(stdin);
	gets(u.nombre);
	printf("Introduce el apellido: /n");
	fflush(stdout);
	fflush(stdin);
	gets(u.apellido);
	printf("Introduzca el dni");
	fflush(stdout);
	fflush(stdin);
	gets(u.dni);
	printf("Introduzca el numero de tarjeta");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&u.numTarjeta);
	return u;

}

void mostrarUsuario(Usuario u){
	printf("%10s%10s%10d", u.nombre, u.apellido,u.dni);
	fflush(stdout);
}

int contrasenyaCorrecta(char * conU, char con){
	int correcta = 0;
	if(strcmp(conU, con) == 0){
		correcta = 1;
	}
	return correcta;
}

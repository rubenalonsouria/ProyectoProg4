#include "admin.h"

#include <stdio.h>
#include <string.h>

Admin conseguirAdmin(){
	Admin a;
	printf("Introduce el nombre: \n");
	fflush(stdout);
	fflush(stdin);
	gets(a.nombre);
	printf("Introduce el apellido: \n");
	fflush(stdout);
	fflush(stdin);
	gets(a.apellido);
	printf("Introduzca el dni \n");
	fflush(stdout);
	fflush(stdin);
	gets(a.dni);
	printf("Introduzca el numero de tarjeta:  \n");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",a.numTarjeta);
	printf("Introduzca la contraseña: \n");
	fflush(stdout);
	fflush(stdin);
	gets(a.contrasenya);
	return a;

}

void mostrarAdmin(Admin a){
	printf("%10s%10s%10d", a.nombre, a.apellido,a.dni);
	fflush(stdout);
}

int contrasenyaCorrectaAdmin(char *conA, char *con){
	int correcta = 0;
	if(strcmp(conA, con) == 0){
		correcta = 1;
	}
	return correcta;
}



#ifndef USUARIO_H_
#define USUARIO_H_
typedef struct usuario{
	char nombre[20];
	char apellido[20];
	char dni[8];
	int numTarjeta[12];
	char contrasenya[20];
}Usuario;

Usuario conseguirUsuario();
void mostrarUsuario();
int contrasenyaCorrecta(char *conU, char *con);


#endif

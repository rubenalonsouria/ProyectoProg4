#include <stdio.h>
#include <stdlib.h>
#include "listaUsuarios.h"
#include "menus.h"
int main(){
	ListaUsuarios lu;
	Usuario u;
	int pos;
	char opcion,opcionU;

	do{
		opcion = menuPrincipal();
		switch(opcion){
		case '0': printf("Cerrando programa\n"); fflush(stdout);break;
		case '1': u = conseguirUsuario();
		          pos = buscarUsuario(lu, u.nombre);
		          if(pos == -1){
		        	  printf("No existe este registro\n");
		          }else{
		        	  if(contrasenyaCorrecta(lu.aUsuarios[pos].contrasenya, u.contrasenya)){
		        		  printf("Bienvenido/n");fflush(stdout);
		        		  do{
		        			  opcionU = menuUsuario();
		        			  switch(opcionU){
		        			  case '0' : printf("Volviendo al menu principal\n"); fflush(stdout);break;
		        			  case '1': break;
		        			  case '2': break;
		        			  case '3': break;
		        			  case '4': break;
		        			  default: printf("La opcion seleccionada no es correcta\n");
		        			  }
		        		  }while(opcionU!= '0');
		        	  }else {
		        		  printf("La contraseña no es correcta\n");fflush(stdout);
		        	  }
		          }
		        break;
		case '2': u = conseguirUsuario();
				  pos = buscarUsuario(lu, u.nombre);
				  if(pos!=-1){
					  printf("Ese nombre de usuario ya existe\n");
				  }else{
					  aniadirUsuario(&lu, u);
				  }
				  break;
		default: printf("La opcion seleccionada no es correcta\n");fflush(stdout);
		}
	}while (opcion != '0');
	free(lu.aUsuarios);
}

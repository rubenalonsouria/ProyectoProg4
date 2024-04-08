
#ifndef LISTAADMIN_H_
#define LISTAADMIN_H_

#include "Admin.h"
typedef struct listaAdmin{
	Admin * aAdmin;
	int tam;
	int numA;
}ListaAdmin;

int buscarAdmin(ListaAdmin lA, char *nom);
void aniadirAdmin(ListaAdmin *lA, Admin A);
void aniadirAdmin(ListaAdmin *la, Admin A);
void volcarListaAdminAFichero(ListaAdmin la, char *nomfich);
void aniadirAdminAlFinalDelFichero(Admin a, char *nomfich);

#endif /* LISTAADMIN_H_ */

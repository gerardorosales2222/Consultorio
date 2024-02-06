#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "estructuras.h"

Usuarios rec;
void registrarRecepcionista();

FILE *archRec, *archPro;

main(){
	int op;
	archRec = fopen("recepcionistas.dat","ab");
	archPro = fopen("profesionales.dat","ab");
	do{
		system("CLS");
        printf("Modulo Administracion \n");
        printf("========================= \n");
        printf("1.- Registrar Profesionales \n");
        printf("2.- Registrar Usuario Recepcionista \n");
        printf("3.- Atenciones por Profesional \n");
		printf("5.- Ranking de Profesionales por Atenciones \n");
		printf("6.- Cerrar la aplicacion. \n");
    	printf("Ingrese una opcion: ");		
		scanf("%d",&op);
		switch(op){
			case 1:
				system("CLS");
				printf("Activado opcion 1...\n");
				system("pause");
				break;
			case 2:
				system("CLS");
				registrarRecepcionista();
				system("pause");
				break;
			case 0:
				break;
			default:
				printf("Ingrese otra opcion...");
		}
	}while(op!=6);
}

void registrarRecepcionista(){
	printf("Ingrese usuario: ");
	scanf("%s", &rec.Usuario);
	printf("Ingrese Contrasenia: ");
	scanf("%s", &rec.Contrasenia);
	printf("Ingrese Apellido y Nombre: ");
	scanf("%s", &rec.ApeNom);
	fwrite(&rec,sizeof(rec),1,arch);
	fclose(arch);
}

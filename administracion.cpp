#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "estructuras.h"

Usuarios rec;
void registrarRecepcionista(FILE *archRec);
bool verificarUsuario(char user[10]);

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
		printf("4.- Ranking de Profesionales por Atenciones \n");
		printf("5.- Cerrar la aplicacion. \n");
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
				registrarRecepcionista(archRec);
				system("pause");
				break;
			case 5:
				printf("Saliendo...");
				break;
			default:
				printf("Ingrese otra opcion...");
		}
	}while(op!=5);
}

void registrarRecepcionista(FILE *archRec){
	char user[10];
	_flushall();
	do{
		printf("Ingrese usuario: ");
		gets(user);
	}while(verificarUsuario(user)==false);
	strcpy(rec.Usuario,user);
	printf("Ingrese Contrasenia: ");
	gets(rec.Contrasenia);
	_flushall();
	printf("Ingrese Apellido y Nombre: ");
	gets(rec.ApeNom);
	_flushall();
	fwrite(&rec,sizeof(rec),1,archRec);
	fclose(archRec);
}

bool verificarUsuario(char user[10]){
	if(strlen(user)>=6 && strlen(user)<=10){
		return true;
	}else{
		printf("Debe tener de 6 a 10 letras.\n");
		return false;
	}
}

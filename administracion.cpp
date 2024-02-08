#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "estructuras.h"

Usuarios rec;
void registrarRecepcionista(FILE *archRec);
bool verificarUsuario(char user[10]);
bool autenticar();

FILE *archRec, *archPro;

main(){
	int op;
	archRec = fopen("recepcionistas.dat","ab");
	archPro = fopen("profesionales.dat","ab");
	if(autenticar()){
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
					archRec = fopen("recepcionistas.dat","ab");
					registrarRecepcionista(archRec);
					fclose(archRec);
					system("pause");
					break;
				case 5:
					printf("Saliendo...");
					break;
				default:
					printf("Ingrese otra opcion...");
			}
		}while(op!=5);
	}else{
		printf("Usuario o contrasenia incorrecto. ");
	}
	
}

bool autenticar(){
	FILE *arch = fopen("recepcionistas.dat", "rb");
	char usuario[10], contrasenia[40];
	bool coincidencia = false;
    if (arch == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }else{
    	printf("Usuario: ");
    	gets(usuario);
    	printf("Contrasenia: ");
    	gets(contrasenia);
    	while (fread(&rec, sizeof(rec), 1, arch) == 1) {
	        if(strcmp(usuario,rec.Usuario)==0&&strcmp(contrasenia,rec.Contrasenia)==0){
	        	coincidencia = true;
	        	printf("COINCIDE\n");
			}
    	}
    }
    return coincidencia;
    fclose(arch);
}

void registrarRecepcionista(FILE *archRec){
	char user[10];
	_flushall();
	rec.baja=0;
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
}

bool verificarUsuario(char user[10]){
	if(strlen(user)>=6 && strlen(user)<=10){
		return true;
	}else{
		printf("Debe tener de 6 a 10 letras.\n");
		return false;
	}
}

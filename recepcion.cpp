#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"

void recuperarUsuarios(FILE *archRec);
void recuperarProfesionales(FILE *archPro);
FILE *archRec, *archPro, *archPac, *archTur;

int main() {
	int op;
	bool sesion=false;
    Usuarios rec;
    Profesionales pro;
    do{
    	system("CLS");
    	printf("\n Modulo del recepcionista");
    	printf("\n =========================");
    	printf("\n 1.- Iniciar Sesion");
    	printf("\n 2.- Registrar Pacientes");
    	printf("\n 3.- Registrar Turno");
    	printf("\n 4.- Listado de Atenciones por Profesional y Fecha");
    	printf("\n 5.- Cerrar la aplicacion.");
    	printf("\n Ingrese una opcion: ");
    	scanf("%d",&op);
    	switch(op){
    		case 1:
    			break;
    		case 2:
    			if(sesion){
    				printf("Registrar Paciente: ");
    			}else{
    				printf("Primero debe iniciar sesion ");
    			}
    			system("PAUSE");
    			break;
    	}
    }while(op!=5);

    recuperarUsuarios(archRec);
    printf("\n");
	recuperarProfesionales(archPro);
    return 0;
}

void recuperarUsuarios(FILE *archRec){
	Usuarios rec;
	archRec = fopen("recepcionistas.dat", "rb");
    if (archRec == NULL) {
        printf("Error al abrir el archivo.\n");
    }

    while (fread(&rec, sizeof(rec), 1, archRec) == 1) {
        printf("User: %s\n", rec.Usuario);
        printf("Name: %s\n", rec.ApeNom);
        printf("Baja: %d\n", rec.baja);
    }
    fclose(archRec);
}


void recuperarProfesionales(FILE *archPro){
	Profesionales pro;
	archPro = fopen("profesionales.dat", "rb");
	while(fread(&pro, sizeof(pro), 1, archPro) == 1){
		printf("Medico: %s\n", pro.ApeNom);
        printf("Tel: %s\n", pro.Telefono);
	}
	fclose(archPro);
}

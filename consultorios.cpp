#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

FILE *f_prof, *f_turnos;
bool autenticar();
void listarTurnos(FILE *f_turnos);

main()
{ 
	int op;
	bool sesion=false;
    do{
    	system("CLS");
    	printf("Modulo del recepcionista\n");
    	printf("=========================\n");
    	printf("\n1.- Iniciar Sesi%cn\n",162);
    	printf("\n2.- Visualizar Lista de Espera de Turnos (informe)\n");
    	printf("\n3.- Registrar Historia Cl%cnica\n",161);
    	printf("\n4.- \n");
    	printf("\n5.- Cerrar la aplicacion\n");
    	printf("\nIngrese una opci%cn: ",162);
    	scanf("%d",&op);
    	switch(op){
    		case 1:
    			system("CLS");
    			if(autenticar()){
    				sesion=true;
    				printf("\nAutenticado \n");
    			}else{
    				printf("\nUsuario o contrase%ca incorrecta \n",164);
    			}
    			system("PAUSE");
    			break;
    		case 2:
    			system("CLS");
    			f_turnos = fopen("turnos.dat", "rb");
    			listarTurnos(f_turnos);
    			system("PAUSE");
    			fclose(f_turnos);
    			break;
    		case 3:
    			
    			system("PAUSE");
    			break;
    		case 4:
    			
    			system("PAUSE");
				break;
    	}
    }while(op!=5);
    return 0;

}

bool autenticar(){
	Usuarios rec;
	FILE *arch = fopen("recepcionistas.dat", "rb");
	char usuario[10], contrasenia[40];
	bool coincidencia = false;
    if (arch == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }else{
    	_flushall();
    	printf("Usuario: ");
    	gets(usuario);
    	_flushall();
    	printf("Contrase%ca: ",164);
    	gets(contrasenia);
    	while (fread(&rec, sizeof(rec), 1, arch) == 1) {
	        if(strcmp(usuario,rec.Usuario)==0&&strcmp(contrasenia,rec.Contrasenia)==0){
	        	coincidencia = true;
			}
    	}
    }
    return coincidencia;
    fclose(arch);
}


void listarTurnos(FILE *f_turnos){
	Turnos tur;
	int pro;
	Fecha f;
	if (f_turnos == NULL) {
      printf("Error al abrir el archivo.\n");
  	}
	printf("Pendientes de atenci%cn: ",162);
  	while (fread(&tur, sizeof(tur), 1, f_turnos) == 1) {
	{
	  	printf("\nProfesional: %d \n", tur.IdProfesional);
    	printf("Fecha: %d/%d/%d\n", tur.FechaAtencion.dia,tur.FechaAtencion.mes,tur.FechaAtencion.anio);
  		printf("Detalle: %s \n", tur.DetalleAtencion);
	}
  }
}

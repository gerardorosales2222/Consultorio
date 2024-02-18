#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "structs.h"

FILE *f_profesionales, *f_turnos, *f_pacientes;
bool autenticar();
void listarTurnos(FILE *archTur, FILE *archPro, FILE *archPac);

int main()
{ 
	int op;
	bool sesion=false;
    do{
    	system("CLS");
	    printf("\n\n\n\t\t  M%cDULO CONSULTORIO \n",224);
	    printf("\t======================================== \n");
    	printf("\n\t 1.- Iniciar Sesi%cn",162);
    	printf("\n\t 2.- Visualizar Lista de Espera de Turnos (informe)");
    	printf("\n\t 3.- Registrar Historia Cl%cnica ",161);
    	printf("\n\t 4.- ");
    	printf("\n\t 5.- Cerrar la aplicacion\n");
    	printf("\n\tIngrese una opci%cn: ",162);
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
    			f_profesionales = fopen("profesionales.dat", "rb");
    			f_pacientes = fopen("pacientes.dat", "rb");
    			listarTurnos(f_turnos, f_profesionales, f_pacientes);
    			system("PAUSE");
    			fclose(f_turnos);
    			fclose(f_profesionales);
    			fclose(f_pacientes);
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
	char caracter;
    if (arch == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }else{
    	_flushall();
    	printf("\n\n\n\n\t\t------------------------------");
    	printf("\n\t\t Autenticaci%cn	\n",162);
    	printf("\t\t------------------------------\n");
    	printf("\t\t Usuario: ");
    	gets(usuario);
    	printf("\t\t Contrase%ca: ",164);
    	int i = 0;
    	while(caracter = getch()){
    		if(caracter == 13){
    			contrasenia[i] = '\0';
    			break;
    		}else{
    			if(caracter == 8){
    				if(i>0){
    					i--;
    					printf("\b \b");
    				}
				}else{
	    			printf("*");
	    			contrasenia[i] = caracter;
	    			i++;
	    		}
    		}    			
    	}
    	while (fread(&rec, sizeof(rec), 1, arch) == 1) {
	        if(strcmp(usuario,rec.Usuario)==0&&strcmp(contrasenia,rec.Contrasenia)==0){
	        	coincidencia = true;
	        	system("COLOR CF");
				system("CLS");
			}
    	}
    }
    return coincidencia;
    fclose(arch);
}

void listarTurnos(FILE *archTur, FILE *archPro, FILE *archPac){
	Turnos tur;
	Profesionales Pro;
	Pacientes Pac;
	int prof;
	Fecha f;
	if (archTur == NULL) {
      printf("Error al abrir el archivo.\n");
  	}
	
	printf("\n\n");
  	while (fread(&tur, sizeof(tur), 1, archTur) == 1) {
  	if(tur.baja == 0)
	{
		while (fread(&Pro, sizeof(Pro), 1, archPro) == 1) {
	    	if (Pro.IdProfesional == tur.IdProfesional) {
	        	printf(" Profesional: %d - %s \n",Pro.IdProfesional, Pro.ApeNom);
			}
		}
		while (fread(&Pac, sizeof(Pac), 1, archPac) == 1) {
	    	if (Pac.DNI == tur.DNI) {
	        	printf(" Paciente: %d - %s \n",Pac.DNI, Pac.ApeNom);
			}
		}
    printf(" Fecha: %d/%d/%d\n", tur.FechaAtencion.dia,tur.FechaAtencion.mes,tur.FechaAtencion.anio);
  	printf(" Detalle: %s \n", tur.DetalleAtencion);
  	}
  	rewind(archPro);
  	rewind(archPac);
  }
  printf("\n");
}

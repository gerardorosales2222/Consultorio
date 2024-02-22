#include "registros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

FILE *f_profesionales, *f_turnos, *f_pacientes;
bool autenticar();
void listarTurnos(FILE *f_turnos, FILE *f_profesionales, FILE *f_pacientes);
void modificarHC();
	
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
    	printf("\n\t 4.- Cerrar la aplicacion\n");
    	printf("\n\tIngrese una opci%cn: ",162);
    	scanf("%d",&op);
    	switch(op){
    		case 1:
    			system("CLS");
    			if(autenticar()){
    				sesion=true;
    				printf("\n\n\n Autenticado \n ");
    			}else{
    				printf("\n Usuario o contrase%ca incorrecta \n ",164);
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
    			system("CLS");
    			modificarHC();
    			system("PAUSE");
    			break;
    		case 4:
				break;
    	}
    }while(op!=4);
    return 0;
}

bool autenticar(){
	Usuarios rec;
	FILE *f_usuarios = fopen("recepcionistas.dat", "rb");
	char usuario[10], contrasenia[40];
	bool coincidencia = false;
	char caracter;
    if (f_usuarios == NULL) {
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
    	while (fread(&rec, sizeof(rec), 1, f_usuarios) == 1) {
	        if(strcmp(usuario,rec.Usuario)==0&&strcmp(contrasenia,rec.Contrasenia)==0){
	        	coincidencia = true;
	        	system("COLOR CF");
				system("CLS");
			}
    	}
    }
    return coincidencia;
    fclose(f_usuarios);
}

void listarTurnos(FILE *f_turnos, FILE *f_profesionales, FILE *f_pacientes){
	Turnos tur;
	Profesionales Pro;
	Pacientes Pac;
	int prof;
	Fecha f;
	if (f_turnos == NULL) {
      printf("Error al abrir el archivo.\n");
  	}
	
	printf("Informe Lista de espera\n\n");
  	while (fread(&tur, sizeof(tur), 1, f_turnos) == 1) {
  	if(tur.baja == 0)
	{
		while (fread(&Pro, sizeof(Pro), 1, f_profesionales) == 1) {
	    	if (Pro.IdProfesional == tur.IdProfesional) {
	        	printf(" Profesional: %d - %s |",Pro.IdProfesional, Pro.ApeNom);
			}
		}
		while (fread(&Pac, sizeof(Pac), 1, f_pacientes) == 1) {
	    	if (Pac.DNI == tur.DNI) {
	        	printf(" Paciente: %d - %s \n",Pac.DNI, Pac.ApeNom);
			}
		}
	printf(" Detalle: %s \n", tur.DetalleAtencion);
    printf(" Fecha: %d/%d/%d\n\n", tur.FechaAtencion.dia,tur.FechaAtencion.mes,tur.FechaAtencion.anio);
  	}
  	rewind(f_profesionales);
  	rewind(f_pacientes);
  }
  printf("\n");
}

void listarPacientes(){
	FILE *f_pacientes = fopen("pacientes.dat","r+b");
	Pacientes Pac;
	printf("	Pacientes \n");
	while(fread(&Pac, sizeof(Pac), 1, f_pacientes) == 1){
		printf("	DNI: %d - %s - %s\n",Pac.DNI, Pac.ApeNom, Pac.HC);
	}
	fclose(f_pacientes);
}

void modificarHC(){
	int dni_buscado;
	Pacientes Pac;
	listarPacientes();
	FILE *f_pacientes = fopen("pacientes.dat","rb");
	printf("\n Ingrese el DNI de paciente a atender: ");
	scanf("%d",&dni_buscado);
	while (fread(&Pac, sizeof(Pac), 1, f_pacientes) == 1) {
	    if (Pac.DNI == dni_buscado) {
			printf("Historia Clinica: ");
			scanf("%s",&Pac.HC);
			long negSize = -(long)sizeof(Pacientes);
			fseek(f_pacientes, negSize, SEEK_CUR);
			fwrite(&Pac, sizeof(Pac), 1, f_pacientes);	
	    break;
	    }
	}
	fclose(f_pacientes);
}

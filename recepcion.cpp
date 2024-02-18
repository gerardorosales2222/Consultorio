//Usuario: adminUTN // Contraseña: admin

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "structs.h"

void listarTurnos(FILE *archTur, FILE *archPro, FILE *archPac);
FILE *archPro, *archPac, *archTur;

bool autenticar();
void listarMedicos();
void listarPacientes();
void registrarPaciente(FILE *archPac);
void registrarTurno(FILE *archPac);

int main(){
	system("TITLE RECEPCION");
	int op;
	bool sesion=false;
    Usuarios rec;
    Profesionales pro;
    do{
    	system("CLS");
		printf("\n\n\n\t\t\t    M%cDULO RECEPCI%cN \n",224,224);
	    printf("\t\t======================================== \n\n");
    	printf("\t\t 1.- Iniciar Sesi%cn\n",162);
    	printf("\t\t 2.- Registrar Pacientes\n");
    	printf("\t\t 3.- Registrar Turno\n");
    	printf("\t\t 4.- Listado de Atenciones por Profesional y Fecha\n");
    	printf("\t\t 5.- Cerrar la aplicaci%cn\n",162);
    	printf("\n\t\tIngrese una opci%cn: ",162);
    	scanf("%d",&op);
    	switch(op){
    		case 1:
    			system("CLS");
    			if(autenticar()){
    				sesion=true;
    				system("COLOR 3F");
    				printf("\n\n\n\n\n\tAutenticado \n\t");
    			}else{
    				printf("\n\n\n\n\nUsuario o contrasenia incorrecta. ");
    			}
    			system("PAUSE");
    			break;
    		case 2:
    			system("CLS");
    			if(sesion){
    				archPac = fopen("pacientes.dat","a+b");
    				registrarPaciente(archPac);
    				fclose(archPac);
    			}else{
    				printf("\n\n\n\n\n   PRIMERO DEBE INICIAR SESION. ");
    			}
    			system(" PAUSE");
    			break;
    		case 3:
    			system("CLS");
    			if(sesion){
    				archTur = fopen("turnos.dat","a+b");
    				registrarTurno(archTur);
    				fclose(archTur);
    			}else{
    				printf("\n\n\n\n\n   PRIMERO DEBE INICIAR SESION. ");
    			}
    			system("PAUSE");
    			break;
    		case 4:
    			system("CLS");
				archTur = fopen("turnos.dat","rb");
				archPro = fopen("profesionales.dat","r+b");
				archPac = fopen("pacientes.dat","r+b");
    			listarTurnos(archTur, archPro, archPac);
    			fclose(archTur);
    			fclose(archPro);
    			system("PAUSE");
				break;
    	}
    }while(op!=5);
    printf("\n\n\n");
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
	        	system("COLOR 2F");
				system("CLS");
			}
    	}
    }
    return coincidencia;
    fclose(arch);
}

void registrarPaciente(FILE *archPac){
	Pacientes pac;
	pac.baja = 0;
	printf("\n REGISTRAR PACIENTE \n");
	printf(" ------------------------------\n\n");
	_flushall();
	printf(" Apellido y Nombre: ");
	gets(pac.ApeNom);
	_flushall();
	printf(" DNI: ");
	gets(pac.DNI);
	_flushall();
	printf(" Localidad: ");
	gets(pac.Localidad);
	_flushall();
	printf(" Tel: ");
	gets(pac.Telefono);
	_flushall();
	printf(" Fecha de Nac \n ->Dia: ");
	scanf("%d",&pac.FechaDeNac.dia);	
	printf(" ->Mes: ");
	scanf("%d",&pac.FechaDeNac.mes);
	printf(" ->A%co: ",164);
	scanf("%d",&pac.FechaDeNac.anio);
	fwrite(&pac,sizeof(pac),1,archPac);	
}

void listarMedicos(){
	FILE *archPro = fopen("profesionales.dat","r+b");
	Profesionales Pro;
	printf("	M%cdicos disponibles \n",130);
	while(fread(&Pro, sizeof(Pro), 1, archPro) == 1){
		printf("	ID: %d		Nombre: %s \n",Pro.IdProfesional, Pro.ApeNom);
	}
}

void listarPacientes(){
	FILE *archPac = fopen("pacientes.dat","r+b");
	Pacientes Pac;
	printf("	Pacientes \n");
	while(fread(&Pac, sizeof(Pac), 1, archPac) == 1){
		printf("	DNI: %s 	Nombre: %s Tel:%s\n",Pac.DNI,Pac.ApeNom,Pac.Telefono);
	}
	fclose(archPac);
}

void registrarTurno(FILE *archTur){
	Turnos tur;
	tur.baja = 0;
	printf("\n REGISTRAR TURNO \n");
	printf(" --------------------------------------------------\n\n");
	listarMedicos();
	printf(" --------------------------------------------------");
	_flushall();
	printf("\n ID M%cdico: ",130);
	scanf("%d",&tur.IdProfesional);
	_flushall();
	printf(" Fecha de Atenci%cn \n ->D%ca: ",162,161);
	scanf("%d",&tur.FechaAtencion.dia);	
	printf(" ->Mes: ");
	scanf("%d",&tur.FechaAtencion.mes);
	printf(" ->A%co: ",164);
	scanf("%d",&tur.FechaAtencion.anio);
	_flushall();
	printf(" --------------------------------------------------\n");
	listarPacientes();
	printf(" --------------------------------------------------\n");
	printf(" DNI Paciente: ");
	gets(tur.DNI);
	_flushall();
	printf(" Detalle atenci%cn: ",162);
	gets(tur.DetalleAtencion);
	_flushall();
	fwrite(&tur,sizeof(tur),1,archTur);
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
	printf("Ingrese ID del profesional: ");
	scanf("%d",&prof);
	printf("Ingrese Fecha de Atencion \n->Dia: ");
	scanf("%d",&f.dia);	
	printf("->Mes: ");
	scanf("%d",&f.mes);
	printf("->A%co: ",164);
	scanf("%d",&f.anio);
  	while (fread(&tur, sizeof(tur), 1, archTur) == 1) {
  	if(tur.IdProfesional == prof 
	&& tur.FechaAtencion.anio == f.anio
	&& tur.FechaAtencion.mes == f.mes
	&& tur.FechaAtencion.dia == f.dia)
	{
		while (fread(&Pro, sizeof(Pro), 1, archPro) == 1) {
	    	if (Pro.IdProfesional == tur.IdProfesional) {
	        	printf(" Profesional: %d - %s \n",Pro.IdProfesional, Pro.ApeNom);
			}
		}
		while (fread(&Pac, sizeof(Pac), 1, archPac) == 1) {
	    	if (strcmp(Pac.DNI, tur.DNI) == 1) {
	        	printf(" Paciente: %s - %s \n",Pac.DNI, Pac.ApeNom);
			}
		}
    printf(" Fecha: %d/%d/%d\n", tur.FechaAtencion.dia,tur.FechaAtencion.mes,tur.FechaAtencion.anio);
  	printf(" Detalle: %s \n", tur.DetalleAtencion);
  	}
  }
  printf("\n");
}

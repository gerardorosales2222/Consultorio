#include<stdio.h>

struct Fecha{
	int dia;
	int mes;
	int anio;
};

struct Pacientes{
	char ApeNom[60];
	int DNI;
	char Localidad[60];	
	struct Fecha FechaDeNac;
	char Telefono[25];
	char HC[380];
	int baja;
};

void listarPacientes();

int main(){
	listarPacientes();	
	return 0;
}

void listarPacientes(){
	FILE *f_pac = fopen("pacientes.dat","r+b");
	Pacientes pac;
	while(fread(&pac,sizeof(Pacientes),1,f_pac) == 1){
		printf("%s - %s", pac.ApeNom, pac.Localidad);
	}
	fclose(f_pac);
}

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
	FILE *f_pacientes = fopen("pacientes.dat","r+b");
	Pacientes Pac;
	printf("	Pacientes \n");
	while(fread(&Pac, sizeof(Pac), 1, f_pacientes) == 1){
		printf("	DNI: %d - %s - %s\n",Pac.DNI, Pac.ApeNom, Pac.HC);
	}
	fclose(f_pacientes);
}

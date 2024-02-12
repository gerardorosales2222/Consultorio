#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"

void recuperarUsuarios(FILE *archRec);
void recuperarProfesionales(FILE *archPro);
void listarTurnos(FILE *archPro);
FILE *archRec, *archPro, *archPac, *archTur;

bool autenticar();
void registrarPaciente(FILE *archPac);
void registrarTurno(FILE *archPac);

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
    			system("CLS");
    			if(autenticar()){
    				sesion=true;
    				printf("\nAutenticado \n");
    			}else{
    				printf("\nUsuario o contrasenia incorrecta \n");
    			}
    			system("PAUSE");
    			break;
    		case 2:
    			if(sesion){
    				system("CLS");
    				archPac = fopen("pacientes.dat","wb");
    				registrarPaciente(archPac);
    				fclose(archPac);
    			}else{
    				printf("\n	PRIMERO DEBE INICIAR SESION \n	");
    			}
    			system(" PAUSE");
    			break;
    		case 3:
    			if(sesion){
    				system("CLS");
    				archTur = fopen("turnos.dat","wb");
    				registrarTurno(archTur);
    				fclose(archTur);
    			}else{
    				printf("\n	PRIMERO DEBE INICIAR SESION \n	");
    			}
    			system(" PAUSE");
    			break;
    		case 4:
    			archTur = fopen("turnos.dat","rb");
    			listarTurnos(archTur);
    			fclose(archTur);
    			system("PAUSE");
					break;
    	}
    }while(op!=5);

    recuperarUsuarios(archRec);
    printf("\n");
	recuperarProfesionales(archPro);
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
    	printf("Contrasenia: ");
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

void registrarPaciente(FILE *archPac){
	Pacientes pac;
	pac.baja = 0;
	_flushall();
	printf("Ingrese Apellido y Nombre: ");
	gets(pac.ApeNom);
	_flushall();
	printf("DNI: ");
	gets(pac.DNI);
	_flushall();
	printf("Localidad: ");
	gets(pac.Localidad);
	_flushall();
	printf("Tel: ");
	gets(pac.Telefono);
	_flushall();
	printf("Fecha de Nac \n->Dia: ");
	scanf("%d",&pac.FechaDeNac.dia);	
	printf("->Mes: ");
	scanf("%d",&pac.FechaDeNac.mes);
	printf("->Anio: ");
	scanf("%d",&pac.FechaDeNac.anio);
	_flushall();
	fwrite(&pac,sizeof(pac),1,archPac);	
}

void registrarTurno(FILE *archTur){
	Turnos tur;
	tur.baja = 0;
	_flushall();
	printf("ID Medico: ");
	scanf("%d",&tur.IdProfesional);
	_flushall();
	printf("Fecha Atencion \n->Dia: ");
	scanf("%d",&tur.FechaAtencion.dia);	
	printf("->Mes: ");
	scanf("%d",&tur.FechaAtencion.mes);
	printf("->Anio: ");
	scanf("%d",&tur.FechaAtencion.anio);
	_flushall();
	printf("DNI Paciente: ");
	gets(tur.DNI);
	_flushall();
	printf("Detalle atencion: ");
	gets(tur.DetalleAtencion);
	_flushall();
	fwrite(&tur,sizeof(tur),1,archTur);
}

void listarTurnos(FILE *archPro){
	Turnos tur;
  if (archTur == NULL) {
      printf("Error al abrir el archivo.\n");
  }

  while (fread(&tur, sizeof(tur), 1, archTur) == 1) {
    printf("Profesional: %d\n", tur.IdProfesional);
    printf("Fecha: %d/%d/%d\n", tur.FechaAtencion.dia,tur.FechaAtencion.mes,tur.FechaAtencion.anio);
  	printf("Detalle: %s\n", tur.DetalleAtencion);
  }
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

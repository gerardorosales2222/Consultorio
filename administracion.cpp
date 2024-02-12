/*
Usuario: adminUTN
Contraseña: admin
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "estructuras.h"

Usuarios rec;
Profesionales pro;
void registrarRecepcionista(FILE *archRec);
bool verificarUsuario(char user[10]);
bool verificarContrasenia(char contrasenia[40]);
bool autenticar();

void registrarProfesional(FILE *archPro);
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
	        printf("1.- Registrar Profesional \n");
	        printf("2.- Registrar Usuario Recepcionista \n");
	        printf("3.- Atenciones por Profesional \n");
			printf("4.- Ranking de Profesionales por Atenciones \n");
			printf("5.- Cerrar la aplicacion. \n");
	    	printf("Ingrese una opcion: ");		
			scanf("%d",&op);
			switch(op){
				case 1:
					system("CLS");
					archPro = fopen("profesionales.dat","ab");
					registrarProfesional(archPro);
					fclose(archPro);
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


void registrarProfesional(FILE *archPro){
	Profesionales pro;
	pro.baja=0;
	_flushall();
	printf("Ingrese Apellido y Nombre: ");
	gets(pro.ApeNom);
	_flushall();
	printf("ID Profesional: ");
	scanf("%d",&pro.IdProfesional);
	_flushall();
	printf("DNI: ");
	gets(pro.DNI);
	_flushall();
	printf("Tel: ");
	gets(pro.Telefono);
	_flushall();
	fwrite(&pro,sizeof(pro),1,archPro);
}

void registrarRecepcionista(FILE *archRec){
	char user[10],contrasenia[40];
	_flushall();
	rec.baja=0;
	do{
		printf("Ingrese usuario: ");
		gets(user);
	}while(verificarUsuario(user)==false);
	strcpy(rec.Usuario,user);
	_flushall();
	do{
		printf("Ingrese Contrasenia: ");
		gets(contrasenia);
	}while(verificarContrasenia(contrasenia)==false);
	strcpy(rec.Contrasenia,contrasenia);
	_flushall();
	printf("Ingrese Apellido y Nombre: ");
	gets(rec.ApeNom);
	_flushall();
	fwrite(&rec,sizeof(rec),1,archRec);
}

bool verificarUsuario(char usuario[10]){
	FILE *arch = fopen("recepcionistas.dat", "rb");
	int may=0, digitos=0;
	bool verificado;
	if(strlen(usuario)>=6 && strlen(usuario)<=10){
		verificado = true;
    	for(int i=0;i<strlen(usuario);i++){
			if(usuario[i]>='A' && usuario[i]<='Z'){
				may++;
			}
			if(usuario[i]>='0' && usuario[i]<='9'){
				digitos++;
			}
		}
    	if(usuario[0]>='a'&&usuario[0]<='z'){
				verificado = true;
		}else{
			verificado = false;
			printf("Debe empezar con minusculas ");
		}
    	if(may<2){
				printf("Debe tener al menos dos Mayusculas.\n");
				verificado = false;
			}
		if(digitos>3){
			printf("No puede tener mas de 3 digitos ");
			verificado = false;
		}
		while(fread(&rec, sizeof(rec), 1, arch) == 1) {
	        if(strcmp(usuario,rec.Usuario)==0){
	        	verificado = false;
	        	printf("Ya existe ese nombre de usuario \n");
			}
    	}
	}else{
		printf("Debe tener de 6 a 10 letras.\n");
		verificado = false;
	}
	return verificado;
}

bool verificarContrasenia(char contrasenia[40]){
	int min=0, may=0, num=0;
	char anterior;
	bool verificado = false;
	int longitud = strlen(contrasenia);
	if(longitud>=6 && longitud<=32){
			for(int i=0;i<longitud;i++){
				switch(contrasenia[i])
				{
					case 'a'...'z':
						min++;
						if(contrasenia[i] == anterior+1 || contrasenia[i] == anterior+33){
							verificado = false;
							printf("\nConsecutivos %c %c",anterior,contrasenia[i]);
						}
						break;
					case 'A'...'Z':
						may++;
						verificado = false;
						if(contrasenia[i] == anterior+1 || contrasenia[i] == anterior-31){
							printf("\nConsecutivos %c %c",anterior,contrasenia[i]);
						}
						break;
					case '0'...'9':
						num++;
						break;
					default:
						verificado = false;
						printf("\nNo se acepta. Debe ser alfanumerico. ");
				}
				anterior = contrasenia[i];
		}
		if(num>0 && min>0 && may>0){
			printf("\nContrasenia guardada.\n");
			verificado = true;
		}else{
			printf("\nNo se guardo \n");
			verificado = false;
		}
	}else{
		printf("Debe tener entre 6 y 32 caracteres\n");
		verificado = false;
	}
	return verificado;
}

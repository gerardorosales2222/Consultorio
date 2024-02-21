//Usuario: adminUTN // Contraseña: admin

#include "registros.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

Usuarios rec;
Profesionales pro;
void registrarRecepcionista(FILE *f_usuarios);
bool verificarUsuario(char user[10]);
bool verificarContrasenia(char contrasenia[40]);
bool autenticar();

void registrarProfesional(FILE *f_profesionales);
void listarMedicos();
void modificarProfesional(FILE *f_profesionales);
void listarTurnos(FILE *f_turnos, FILE *f_profesionales, FILE *f_pacientes);
void ranking(FILE *f_profesionales);
FILE *f_usuarios, *f_profesionales, *f_pacientes, *f_turnos;

main(){
	system("TITLE ADMINISTRACIÓN");
	int op;
	f_usuarios = fopen("recepcionistas.dat","ab");
	f_profesionales = fopen("profesionales.dat","ab");
	if(autenticar()){
		do{
			system("CLS");
	        printf("\n\n\n\t\t\t  M%cDULO ADMINISTRACI%cN \n",224,224);
	        printf("\t\t======================================== \n\n");
	        printf("\t\t 1.- Registrar Profesional \n");
	        printf("\t\t 2.- Registrar Usuario \n");
	        printf("\t\t 3.- Atenciones por Profesional \n");
			printf("\t\t 4.- Ranking de Profesionales \n");
			printf("\t\t 5.- Cerrar la aplicaci%cn. \n\n",162);
	    	printf("\t\tIngrese una opci%cn: ",162);		
			scanf("%d",&op);
			switch(op){
				case 1:
					system("CLS");
					f_profesionales = fopen("profesionales.dat","ab");
					registrarProfesional(f_profesionales);
					fclose(f_profesionales);
					printf("\n\n\n\n\nProfesional registrado. \n");
					system("PAUSE");
					break;
				case 2:
					system("CLS");
					f_usuarios = fopen("recepcionistas.dat","ab");
					registrarRecepcionista(f_usuarios);
					fclose(f_usuarios);
					system("pause");
					break;
				case 3:
					system("CLS");
					f_turnos = fopen("turnos.dat","rb");
					f_profesionales = fopen("profesionales.dat","rb");
					f_pacientes = fopen("pacientes.dat","rb");
					listarTurnos(f_turnos, f_profesionales, f_pacientes);
					fclose(f_turnos);
					system("pause");
					break;
				case 4:
					system("CLS");
					f_turnos = fopen("turnos.dat","rb");
					ranking(f_turnos);
					fclose(f_turnos);
					system("PAUSE");
					break;
				case 5:
					break;
				case 6:
					system("CLS");
					f_profesionales = fopen("profesionales.dat","r+b");
					modificarProfesional(f_profesionales);
					fclose(f_profesionales);
					printf("\n\n\n\n\nProfesional modificado. \n");
					system("PAUSE");
					break;
				default:
					system("CLS");
					printf("\nOpci%cn no v%clida...\n",162,160);
					system("PAUSE");
			}
		}while(op!=5);
		printf("\n\n\n");
	}else{
		system("COLOR 4F");
		system("CLS");
		printf("\n\n\n\n\n\n\n\t\t -----------------------------------");
		printf("\n\t\t   Usuario o contrase%ca incorrecto. \n",164);
		printf("\t\t -----------------------------------\n\n\n\n\n\n\n");
	}
}

bool autenticar(){
	FILE *f_usuarios = fopen("recepcionistas.dat", "rb");
	char usuario[10], contrasenia[40];
	char caracter;
	bool coincidencia = false;
    if (f_usuarios == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }else{
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
	        	system("COLOR 2F");
				system("CLS");
			}
    	}
    }
    return coincidencia;
    fclose(f_usuarios);
}


void registrarProfesional(FILE *f_profesionales){
	Profesionales pro;
	pro.baja=0;
	_flushall();
	printf("\n REGISTRAR PROFESIONAL \n");
	printf(" ------------------------------\n\n");
	printf("\t Apellido y Nombre: ");
	gets(pro.ApeNom);
	_flushall();
	printf("\t ID Profesional: ");
	scanf("%d",&pro.IdProfesional);
	_flushall();
	printf("\t DNI: ");
	gets(pro.DNI);
	_flushall();
	printf("\t Tel: ");
	gets(pro.Telefono);
	_flushall();
	fwrite(&pro,sizeof(pro),1,f_profesionales);
}

void registrarRecepcionista(FILE *f_usuarios){
	char user[10],contrasenia[40];
	_flushall();
	rec.baja=0;
	printf("\n REGISTRAR USUARIO \n");
	printf(" ------------------------------\n\n");
	do{
		printf("\t Ingrese usuario: ");
		gets(user);
	}while(verificarUsuario(user)==false);
	strcpy(rec.Usuario,user);
	_flushall();
	do{
		printf("\t Ingrese Contrase%ca: ",164);
		gets(contrasenia);
	}while(verificarContrasenia(contrasenia)==false);
	strcpy(rec.Contrasenia,contrasenia);
	_flushall();
	printf("\t Ingrese Apellido y Nombre del usuario: ");
	gets(rec.ApeNom);
	_flushall();
	fwrite(&rec,sizeof(rec),1,f_usuarios);
}

bool verificarUsuario(char usuario[10]){
	FILE *f_usuarios = fopen("recepcionistas.dat", "rb");
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
			printf("\t Debe empezar con minusculas \n");
		}
    	if(may<2){
				printf("\t Debe tener al menos dos Mayusculas.\n");
				verificado = false;
			}
		if(digitos>3){
			printf("\t No puede tener mas de 3 digitos \n");
			verificado = false;
		}
		while(fread(&rec, sizeof(rec), 1, f_usuarios) == 1) {
	        if(strcmp(usuario,rec.Usuario)==0){
	        	verificado = false;
	        	printf("\t Ya existe ese nombre de usuario \n");
			}
    	}
	}else{
		printf("\t Debe tener de 6 a 10 letras.\n");
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
						printf("\n No se acepta. Debe ser alfanumerico. ");
				}
				anterior = contrasenia[i];
		}
		if(num>0 && min>0 && may>0){
			printf("\t Contrase%ca OK. \n",164);
			verificado = true;
		}else{
			printf(" No se guard%c. Debe tener al menos un nro, una min%cscula y una may%cscula \n",162,163,163);
			verificado = false;
		}
	}else{
		printf("\t Debe tener entre 6 y 32 caracteres\n");
		verificado = false;
	}
	return verificado;
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
	printf("Ingrese ID del profesional: ");
	scanf("%d",&prof);
	printf("\n\n");
  	while (fread(&tur, sizeof(tur), 1, f_turnos) == 1) {
  	if(tur.IdProfesional == prof)
	{
		while (fread(&Pro, sizeof(Pro), 1, f_profesionales) == 1) {
	    	if (Pro.IdProfesional == tur.IdProfesional) {
	        	printf(" Profesional: %d - %s \n",Pro.IdProfesional, Pro.ApeNom);
			}
		}
		while (fread(&Pac, sizeof(Pac), 1, f_pacientes) == 1) {
	    	if (Pac.DNI == tur.DNI) {
	        	printf(" Paciente: %d - %s \n",Pac.DNI, Pac.ApeNom);
			}
		}
    printf(" Fecha: %d/%d/%d\n", tur.FechaAtencion.dia,tur.FechaAtencion.mes,tur.FechaAtencion.anio);
  	printf(" Detalle: %s \n", tur.DetalleAtencion);
  	if(tur.baja==0){
  		printf(" Estado: Pendiente de atenci%cn \n\n",162);
  	}
  	}
  	rewind(f_profesionales);
  	rewind(f_pacientes);
  }
  printf("\n");
}

void ranking(FILE *f_profesionales){
	Turnos tur;
	int v[100];
	int profesionales[100];
	if (f_turnos == NULL) {
      printf("Error al abrir el archivo.\n");
  	}
  	int i = 0, longitud = 0;
	while(fread(&tur, sizeof(tur), 1, f_turnos) == 1){	
		v[i]=tur.IdProfesional;
		i++;
		longitud++;
	}
	
	int maxCount = 0; // Contador máximo de apariciones
    int masFrecuente = 0; // Número más frecuente

    for (int i = 0; i < longitud; i++) {
        int count = 0; // Contador para el elemento actual
        for (int j = 0; j < longitud; j++) {
            if (v[i] == v[j]) {
                count++; // Incrementar el contador si encontramos el mismo elemento
            }
        }
        if (count > maxCount) {
            maxCount = count; // Actualizar el contador máximo y el número más frecuente
            masFrecuente = v[i];
        }
    }

    printf("El profesional que mas turnos tiene es: %d (tiene %d turnos)\n", masFrecuente, maxCount);
}

void listarMedicos(){
	FILE *archPro = fopen("profesionales.dat","r+b");
	Profesionales Pro;
	printf("\n	Lista de M%cdicos \n",130);
	printf("	--------------------------------------------\n");
	while(fread(&Pro, sizeof(Pro), 1, archPro) == 1){
		if(Pro.baja==0){
			printf("	ID: %d		Nombre: %s \n",Pro.IdProfesional, Pro.ApeNom);
		}
	}
	printf("\n	--------------------------------------------\n");
}

void modificarProfesional(FILE *archPro){
	int id_buscado;
	Profesionales Pro;
	listarMedicos();
	printf("\n Ingrese el ID del m%cdico a modificar: ",130);
	scanf("%d",&id_buscado);
	while (fread(&Pro, sizeof(Pro), 1, archPro) == 1) {
	    if (Pro.IdProfesional == id_buscado) {
	        printf(" %d - %s \n",Pro.IdProfesional, Pro.ApeNom);
	        _flushall();
	        printf("\t Apellido y Nombre: ");
			gets(Pro.ApeNom);
			_flushall();
			printf("\t ID Profesional: ");
			scanf("%d",&Pro.IdProfesional);
			_flushall();
			printf("\t DNI: ");
			gets(Pro.DNI);
			_flushall();
			printf("\t Tel: ");
			gets(Pro.Telefono);	        
	        fseek(archPro, -sizeof(Pro), SEEK_CUR);
			fwrite(&Pro, sizeof(Pro), 1, archPro);
			fclose(archPro);
	        break;
	    }
	}
	
	if (feof(archPro)) {
	    printf("El ID no se corresponde con ning%cn m%cdico de la lista.\n",163,130);
	    fclose(archPro);
	}
	
}

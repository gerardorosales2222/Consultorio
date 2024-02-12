#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fecha
{
	int dia, mes, anio;
};
struct usuario
{
	char username[10];
	char password[10];
	char ApellidoyNombre[60];
};
struct medico
{
	int Id;
	char contra[10];
	int paciente;
};
struct profesional
{
	char ApellidoyNombre [60];
	int id;
	char username[10];
	char password [10];
};
struct paciente
{
	char ApellidoyNombre[60];
	char domicilio[60];
	int DNI;
	fecha fec;
	int edad;
	float peso;
	float altura;
	char historiaclinica[50];
};

struct turnos
{
	char atencion[60];
	int atencion1;
};

int dibujarMenu();
bool iniciarse(FILE *f, int &id);
void historiaclinica(FILE *f);
void lista (FILE *pacientes, FILE *atenciones);

main()
{ 
    FILE *pacientes = fopen("pacientes.dat", "a+b");
    FILE *profesionales = fopen("profesionales.dat", "a+b");
    FILE *atenciones =fopen("atenciones.dat", "a+b");
    FILE *cantp = fopen("cantp.dat", "a+b");
    
    if (profesionales == NULL)
    {
    	printf("profesionales.dat no ha sido creado.\n\n");
		system("pause");
		exit(1);
    }
    
   	bool inicio = false, borrar = false;
	int id;
	
		int opc;
	do{
		opc = dibujarMenu();
		switch(opc){
			case 1:	inicio = iniciarse(profesionales, id);		 	 
					 break;
			case 2: if(inicio == true)
						{
						  lista(pacientes,atenciones);
					 	}
						 else printf("\nPrimerio debe Iniciar sesion!\n");
					 break;
			case 3:if(inicio == true)
						{
						  historiaclinica(pacientes);
					 	}
						 else printf("\nPrimerio debe Iniciar sesion!\n");
					 break;
					 }
					 
		printf("\n");
		system("pause");
	}while(opc != 4);
	
	fclose(pacientes);
	
	fclose(profesionales);
	exit(1);

}
int dibujarMenu(){
	system("cls");
	printf("\n\t\t\t******************* Modulo Consultorios*******************\n");
	printf("\n\t\t\t 1) Iniciar Sesion");
	printf("\n\t\t\t 2) Visualizar Lista de Espera de Turnos");
	printf("\n\t\t\t 3) Registrar Historia Clínica");
    printf("\n\t\t\t 4) Cerrar la aplicacion");
	printf("\n\n\t\t\t Ingrese la opcion deseada: ");
	int opc;
	scanf("%d", &opc);
	return opc;
    }
bool iniciarse(FILE *f, int &id)
{
	rewind(f);
	medico log;
	profesional p;
	bool iniciado = false;
	int valor;
	system("cls");
	
	do
	{
		printf("\n - Ingrese ID del profesional: ");
		scanf("%d", &log.Id);
	} while (log.Id >= 9999);
	id = log.Id;
	
	printf("\n - Ingrese contrasena: ");
	_flushall();
	gets(log.contra);
	system("cls");
	
	while(!feof(f))
    {
        valor = strcmp(log.contra, p.password);
        
        if(log.Id == p.id)
		{
			if(valor == 0)
			{	
				printf("\n - Sesion iniciada correctamente");
				printf("\n\n - Bienvenido/a %s!", p.ApellidoyNombre);
				printf("\n");
				iniciado = true;
			}

		}
        fread(&p, sizeof(profesional), 1, f);
    }
    if(iniciado == false) printf("\nEl nombre de usuario y/o contrasena no coinciden\n\n");
    return iniciado;

}

void historiaclinica(FILE *f)
{	
	fclose(f);
	f = fopen("pacientes.dat", "r+b");

	system("cls");
	paciente num;
	int numero;
    int b=0;

	printf("\n - Ingrese numero de paciente: ");
	scanf("%d",&numero);
	system("cls");
    rewind(f);
	fread(&num, sizeof(paciente), 1, f);
	while(!feof(f))
	{  
		if(numero == num.DNI)
		{
			system("cls");
			printf("\n - Detalle de la Historia Clinica: ");
			_flushall();
			gets(num.historiaclinica);
			fwrite(&num, sizeof(paciente), 1, f);
		    b=1;
		}
	
		fread(&num, sizeof(paciente), 1, f);
	}
	if (b==1)
	{
		printf("\n - Atencion registrado\n");
	}
	else
		{
	    printf("\n - Numero de paciente no encontrado!");
		printf("\n - Atencion no registrada\n");	
		} 
	
	fclose(f);
}

void lista(FILE *pacientes, FILE *atenciones)
{
    pacientes = fopen("pacientes.dat", "rb");
    atenciones = fopen("atenciones.dat", "rb");

    if (pacientes == NULL || atenciones == NULL)
    {
        printf("Error al abrir archivos.\n");
        return;
    }

    system("cls");
    struct paciente reg;
    struct turnos a;

    rewind(pacientes);
    fread(&reg, sizeof(struct paciente), 1, pacientes);

    printf("\n\t\t - Listado de pacientes e historia clinica:");
    printf("\n");

    fread(&a, sizeof(struct turnos), 1, atenciones);

    while (!feof(pacientes) && !feof(atenciones))
    {
        printf("\n");
        printf("\n\t\t - *%s ", reg.ApellidoyNombre);
        printf("\n\t\t - Numero de paciente: %d", reg.DNI);

          if(a.atencion1 == 1)
		   {
		   	printf("\n\t\t - Anestesiología");
		   }
		   if(a.atencion1 == 2)
		   {
		   	printf("\n\t\t - Cuidados intensivos");
		   }
		   if(a.atencion1 == 3)
		   {
		   	printf("\n\t\t - Otorrinolaringología");
		   }
		   if(a.atencion1 == 4)
		   {
		   	printf("\n\t\t - Nefrología");
		   }
		   if(a.atencion1 == 5)
		   {
		   	printf("\n\t\t - Oncología");
		   }
		   if(a.atencion1 == 6)
		   {
		   	printf("\n\t\t - Neumología");
		   }
		    if(a.atencion1 == 7)
		   {
		   	printf("\n\t\t - Oftalmología");
		   }
		   if(a.atencion1 == 8)
		   {
		   	printf("\n\t\t - Cardiología");
		   }
		   if(a.atencion1 == 9)
		   {
		   	printf("\n\t\t - Pediatría");
		   }
		   if(a.atencion1 == 10)
		   {
		   	printf("\n\t\t - Clínico");
		   }
		     if(a.atencion1 == 11)
		   {
		   	printf("\n\t\t - Urología");
		   }
		   if(a.atencion1 == 12)
		   {
		   	printf("\n\t\t - Dermatología");
		   }
		   if(a.atencion1 == 13)
		   {
		   	printf("\n\t\t - Obstetricia y Ginecología");
		   }
        fread(&reg, sizeof(struct paciente), 1, pacientes);
        fread(&a, sizeof(struct turnos), 1, atenciones);
    }

    printf("\n");

    fclose(atenciones);
    fclose(pacientes);
}


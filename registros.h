struct Usuarios{
	char Usuario[10];
	char Contrasenia[40];
	char ApeNom[60];
	int baja;
};

struct Profesionales{
	int IdProfesional;
	char ApeNom[60];
	char DNI[8];
	char Telefono[25];
	int baja;
};

typedef struct{
	int dia;
	int mes;
	int anio;
}Fecha;

typedef struct{
	char ApeNom[60];
	int DNI;
	char Telefono[10];
	Fecha FechaDeNac;
	char Localidad[60];
	int baja;
	char HC[380];
}Pacientes;

typedef struct{
	int IdProfesional;
	Fecha FechaAtencion;
	int DNI;
	char DetalleAtencion[380];
	int baja;
}Turnos;

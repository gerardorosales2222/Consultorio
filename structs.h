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
	char DNI[8];
	char Localidad[60];
	Fecha FechaDeNac;
	char Telefono[10];
	int baja;
}Pacientes;

typedef struct{
	int IdProfesional;
	Fecha FechaAtencion;
	char DNI[8];
	char DetalleAtencion[380];
	int baja;
}Turnos;

typedef struct{
	char Usuario[10];
	char Contrasenia[40];
	char ApeNom[60];
	int baja;
}Usuarios;

typedef struct{
	int IdProfesional;
	char ApeNom[60];
	char DNI[8];
	char Telefono[25];
	int baja;
}Profesionales;

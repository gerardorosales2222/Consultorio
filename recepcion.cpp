#include <stdio.h>
#include "estructuras.h"

int main() {
    FILE *arch;
    Usuarios rec;

    arch = fopen("recepcionistas.dat", "rb");
    if (arch == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    while (fread(&rec, sizeof(rec), 1, arch) == 1) {
        printf("User: %s\n", rec.Usuario);
        printf("Name: %s\n", rec.ApeNom);
        printf("Baja: %d\n", rec.baja);
    }

    fclose(arch);

    return 0;
}

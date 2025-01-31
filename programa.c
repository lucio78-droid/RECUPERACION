//examen de recuperacion.
#include <stdio.h>
#include <ctype.h> 
#include "funciones.h"

int placaExiste(const char *placa) {
    FILE *archivo = fopen(ARCHIVO, "rb");
    if (!archivo) return 0;  // Si el archivo no existe, no hay placas repetidas

    Vehiculo v;
    while (fread(&v, sizeof(Vehiculo), 1, archivo)) {
        if (strcmp(v.placa, placa) == 0) {
            fclose(archivo);
            return 1;  // La placa ya existe
        }
    }
    fclose(archivo);
    return 0;  // La placa no existe
}


int esSoloLetras(const char *cadena) {
    while (*cadena) {
        if (!isalpha(*cadena) && *cadena != ' ') {
            return 0; 
        }
        cadena++;
    }
    return 1;
}

int esCedulaValida(const char *cedula) {
    if (strlen(cedula) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(cedula[i])) return 0;
    }
    return 1;
}


int esPlacaValida(const char *placa) {
    if (strlen(placa) != 7) return 0;
    for (int i = 0; i < 3; i++) {
        if (!isalpha(placa[i])) return 0; 
    }
    if (placa[3] != '-') return 0; 
    for (int i = 4; i < 7; i++) {
        if (!isdigit(placa[i])) return 0; 
    }
    return 1;
}

void limpiarBuffer() {
    while (getchar() != '\n'); 
}
void crearVehiculo() {
    FILE *archivo = fopen(ARCHIVO, "ab");
    if (!archivo) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    Vehiculo v;

do {
    printf("Ingrese placa (AAA-123): ");
    scanf("%7s", v.placa);
    if (!esPlacaValida(v.placa)) {
        printf("Error: Formato de placa inválido. Use 'AAA-123'.\n");
    } else if (placaExiste(v.placa)) {
        printf("Error: La placa ya está registrada. Intente con otra.\n");
    }
} while (!esPlacaValida(v.placa) || placaExiste(v.placa));
    printf("Ingrese color: ");
    fgets(v.color, sizeof(v.color), stdin);
    v.color[strcspn(v.color, "\n")] = 0; 

    do {
        printf("Ingrese anio (positivo): ");
        if (scanf("%d", &v.anio) != 1 || v.anio <= 0) {
            printf("Error: El anioo debe ser un numero positivo.\n");
            limpiarBuffer();
        }
    } while (v.anio <= 0);
    limpiarBuffer();

    do {
        printf("Ingrese nombre del duenio: ");
        fgets(v.propietario.nombre, sizeof(v.propietario.nombre), stdin);
        v.propietario.nombre[strcspn(v.propietario.nombre, "\n")] = 0;
        if (!esSoloLetras(v.propietario.nombre)) {
            printf("Error: El nombre solo puede contener letras y espacios.\n");
        }
    } while (!esSoloLetras(v.propietario.nombre));

    do {
        printf("Ingrese cedula del duenio (10 digitos): ");
        scanf("%10s", v.propietario.cedula);
        limpiarBuffer();
        if (!esCedulaValida(v.propietario.cedula)) {
            printf("Error: La cedula debe contener exactamente 10 digitos numericos.\n");
        }
    } while (!esCedulaValida(v.propietario.cedula));

    do {
        printf("Ingrese cilindraje del motor (positivo): ");
        if (scanf("%d", &v.motor.cilindraje) != 1 || v.motor.cilindraje <= 0) {
            printf("Error: El cilindraje debe ser un numero positivo.\n");
            limpiarBuffer();
        }
    } while (v.motor.cilindraje <= 0);
    limpiarBuffer();

    do {
        printf("Ingrese tipo de combustible: ");
        fgets(v.motor.tipoCombustible, sizeof(v.motor.tipoCombustible), stdin);
        v.motor.tipoCombustible[strcspn(v.motor.tipoCombustible, "\n")] = 0;
        if (!esSoloLetras(v.motor.tipoCombustible)) {
            printf("Error: El tipo de combustible solo debe contener letras.\n");
        }
    } while (!esSoloLetras(v.motor.tipoCombustible));

    fwrite(&v, sizeof(Vehiculo), 1, archivo);
    fclose(archivo);
    printf("Vehiculo registrado correctamente.\n");
}

void verVehiculos() {
    FILE *archivo = fopen(ARCHIVO, "rb");
    if (!archivo) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    Vehiculo v;
    printf("\nLista de Vehiculos:\n");
    while (fread(&v, sizeof(Vehiculo), 1, archivo)) {
        printf("Placa: %s, Color: %s, Anio: %d\n", v.placa, v.color, v.anio);
        printf("Duenio: %s, Cedula: %s\n", v.propietario.nombre, v.propietario.cedula);
        printf("Motor: %d cc, Combustible: %s\n\n", v.motor.cilindraje, v.motor.tipoCombustible);
    }
    fclose(archivo);
}

void buscarPorPlaca() {
    FILE *archivo = fopen(ARCHIVO, "rb");
    if (!archivo) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    char placaBuscada[8];
    printf("Ingrese la placa a buscar: ");
    scanf("%7s", placaBuscada);

    Vehiculo v;
    int encontrado = 0;
    while (fread(&v, sizeof(Vehiculo), 1, archivo)) {
        if (strcmp(v.placa, placaBuscada) == 0) {
            printf("\nVehiculo encontrado:\n");
            printf("Placa: %s, Color: %s, Anio: %d\n", v.placa, v.color, v.anio);
            printf("Duenio: %s, Cedula: %s\n", v.propietario.nombre, v.propietario.cedula);
            printf("Motor: %d cc, Combustible: %s\n", v.motor.cilindraje, v.motor.tipoCombustible);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("No se encontro un vehículo con esa placa.\n");
    }
    fclose(archivo);
}

void buscarPorCedula() {
    FILE *archivo = fopen(ARCHIVO, "rb");
    if (!archivo) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    char cedulaBuscada[11];
    printf("Ingrese la cedula a buscar: ");
    scanf("%10s", cedulaBuscada);

    Vehiculo v;
    int encontrado = 0;
    while (fread(&v, sizeof(Vehiculo), 1, archivo)) {
        if (strcmp(v.propietario.cedula, cedulaBuscada) == 0) {
            printf("\nVehiculo encontrado:\n");
            printf("Placa: %s, Color: %s, Anio: %d\n", v.placa, v.color, v.anio);
            printf("Duenio: %s, Cedula: %s\n", v.propietario.nombre, v.propietario.cedula);
            printf("Motor: %d cc, Combustible: %s\n", v.motor.cilindraje, v.motor.tipoCombustible);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("No se encontro un vehículo con esa cedula.\n");
    }
    fclose(archivo);
}
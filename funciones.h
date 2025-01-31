#ifndef VEHICULO_H
#define VEHICULO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO "vehiculos.dat"


typedef struct {
    char nombre[50];
    char cedula[11]; 
} Dueno;
typedef struct {
    int cilindraje;
    char tipoCombustible[20];
} Motor;
typedef struct {
    char placa[8]; 
    char color[20];
    int anio;
    Dueno propietario;
    Motor motor;
} Vehiculo;

void crearVehiculo();
int esSoloLetras(const char *cadena);
int esCedulaValida(const char *cedula);
int esPlacaValida(const char *placa);
void verVehiculos();
void buscarPorPlaca();
void buscarPorCedula();
int placaExiste(const char *placa);
#endif

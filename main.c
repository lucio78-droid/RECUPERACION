#include <stdio.h>
#include "funciones.h"

int main() {
    int opcion;
    do {
        printf("\n--- Sistema de Gestion de Vehiculos ---\n");
        printf("1. Crear Vehiculo\n");
        printf("2. Ver Vehiculos\n");
        printf("3. Buscar por Placa\n");
        printf("4. Buscar por Cedula\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                crearVehiculo();
                break;
            case 2:
                verVehiculos();
                break;
            case 3:
                buscarPorPlaca();
                break;
            case 4:
                buscarPorCedula();
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción invalida. Intente nuevamente.\n");
        }
    } while (opcion != 5);

    return 0;
}

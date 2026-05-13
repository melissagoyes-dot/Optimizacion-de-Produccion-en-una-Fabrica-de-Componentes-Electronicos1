#include <stdio.h>
#include "funciones.h"

int main()
{
    char nombres[MAX_PROD][MAX_NOMBRE];
    int cantidades[MAX_PROD];
    int tiempos[MAX_PROD];
    int recursos[MAX_PROD];
    int totalProductos = 0, opc = 0, opc2 = 0;
    int tiempoDisponible = 0, recursosDisponibles = 0;

    printf("\n-------BIENVENIDX AL PROGRAMA DE GESTION-----\n");
    do
    {
        printf("\n=== FABRICA DE COMPONENTES ELECTRONICOS ===\n");
        printf("1. Ingresar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Calcular tiempo y recursos totales\n");
        printf("5. Gestionar demanda\n");
        printf("6. Salir\n");
        printf(">> ");
        opc = validacionentero(1, 6);

        switch (opc)
        {
        case 1:
            ingresarProducto(nombres, cantidades, tiempos, recursos, &totalProductos);
            break;

        case 2:
            editarProducto(nombres, cantidades, tiempos, recursos, totalProductos);
            break;

        case 3:
            eliminarProducto(nombres, cantidades, tiempos, recursos, &totalProductos);
            break;

        case 4:
            printf("\n--- TOTALES ACTUALES ---\n");
            printf("Tiempo total requerido: %d minutos\n", calcularTiempoTotal(cantidades, tiempos, totalProductos));
            printf("Recursos totales requeridos: %d unidades\n", calcularRecursosTotales(cantidades, recursos, totalProductos));
            break;

        case 5:
            gestionarDemandaYSock(nombres, cantidades, tiempos, recursos, totalProductos, &tiempoDisponible, &recursosDisponibles);
            break;

        case 6:
            opc2 = 1;
            break;
        }
        if (opc != 6)
        {
            printf("\n¿Desea volver al menu principal? (1.Si / 2.No)\n>> ");
            opc2 = validacionentero(1, 2);
        }
    } while (opc2 == 1);

    printf("\nSaliendo del programa..., Gracias vuelva pronto :D\n");
    return 0;
}
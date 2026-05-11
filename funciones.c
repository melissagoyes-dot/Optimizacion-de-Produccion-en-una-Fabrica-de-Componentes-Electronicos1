#include <stdio.h>
#include <string.h>
#include "funciones.h"

int validacionentero(int a, int b)
{
    int n = 0, aux = 0;
    do
    {
        aux = scanf("%d", &n);
        limpiarBuffer();
        if (aux != 1 || n < a || n > b)
        {
            printf("\nERROR: EL DATO INGRESADO ES INCORRECTO, INTENTELO NUEVAMENTE\n>> ");
        }
    } while (aux != 1 || n < a || n > b);
    return n;
}

void limpiarSaltoDeLinea(char cadena[])
{
    cadena[strcspn(cadena, "\n")] = '\0';
}

void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ingresarProducto(char nombres[][MAX_NOMBRE], int *cantidades, int *tiempos, int *recursos, int *totalProductos)
{
    if (*totalProductos < MAX_PROD)
    {
        printf("\n--------INGRESANDO NUEVO PRODUCTO------------\n ");
        printf("\nNombre del producto: ");
        printf("\n>>");
        fgets(nombres[*totalProductos], MAX_NOMBRE, stdin);
        limpiarSaltoDeLinea(nombres[*totalProductos]);
        printf("\nCantidad");
        printf("\n>>");
        cantidades[*totalProductos] = validacionentero(1, 9999999);
        printf("\nTiempo por unidad en minutos: ");
        printf("\n>>");
        tiempos[*totalProductos] = validacionentero(1, 9999999);
        printf("\nRecursos por unidad: ");
        printf("\n>>");
        recursos[*totalProductos] = validacionentero(1, 9999999);
        (*totalProductos)++;
        printf("\nSE HA INGRESADO EL PRODUCTO CON EXITO\n");
    }
    else
    {
        printf("\nERROR: YA SE HAN INGRESADO EL MAXIMO DE PRODUCTOS");
    }
}

int buscarProducto(char nombres[][MAX_NOMBRE], int totalProductos, char nombre[])
{
    for (int i = 0; i < totalProductos; i++)
    {
        if (strcmp(nombres[i], nombre) == 0)
        {
            return i;
        }
    }
    return -1;
}

void editarProducto(char nombres[][MAX_NOMBRE], int *cantidades, int *tiempos, int *recursos, int totalProductos)
{
    if (totalProductos == 0)
    {
        printf("\nERROR: NO HAY PRODUCTOS REGISTRADOS PARA EDITAR\n");
        return;
    }
    char nombre[MAX_NOMBRE];
    printf("\n------EDITOR DE PRODUCTOS----\n");
    printf("\nIngrese el nombre del producto a editar: ");
    printf("\n>>");
    fgets(nombre, MAX_NOMBRE, stdin);
    limpiarSaltoDeLinea(nombre);
    int pos = buscarProducto(nombres, totalProductos, nombre);
    if (pos != -1)
    {
        printf("\nNueva cantidad (actual: %d): ", cantidades[pos]);
        printf("\n>>");
        cantidades[pos] = validacionentero(1, 9999999);
        printf("\nNuevo tiempo por unidad en segundos (actual: %d): ", tiempos[pos]);
        printf("\n>>");
        tiempos[pos] = validacionentero(1, 9999999);
        printf("\nNuevos recursos por unidad (actual: %d): ", recursos[pos]);
        printf("\n>>");
        recursos[pos] = validacionentero(1, 9999999);
        printf("*****Producto editado con exito*********\n");
    }
    else
    {
        printf("\nERROR: PRODUCTO NO ENCONTRADO\n");
    }
}

void eliminarProducto(char nombres[][MAX_NOMBRE], int *cantidades, int *tiempos, int *recursos, int *totalProductos)
{
    if (*totalProductos == 0)
    {
        printf("\nERROR: NO HAY PRODUCTOS DISPONIBLES PARA ELIMIMNAR\n");
        return;
    }
    char nombre[MAX_NOMBRE];
    printf("\n------ELIMINADOR DE PRODUCTOS----\n");
    printf("\nNombre del producto a eliminar: ");
    printf("\n>>");
    fgets(nombre, MAX_NOMBRE, stdin);
    limpiarSaltoDeLinea(nombre);
    int pos = buscarProducto(nombres, *totalProductos, nombre);
    if (pos != -1)
    {
        for (int i = pos; i < (*totalProductos) - 1; i++)
        {
            strcpy(nombres[i], nombres[i + 1]);
            cantidades[i] = cantidades[i + 1];
            tiempos[i] = tiempos[i + 1];
            recursos[i] = recursos[i + 1];
        }
        (*totalProductos)--;
        printf("******Producto eliminado con exito******\n");
    }
    else
    {
        printf("\nERROR: PRODUCTO NO ENCONTRADO\n");
    }
}

int calcularTiempoTotal(int *cantidades, int *tiempos, int totalProductos)
{
    int total = 0;
    for (int i = 0; i < totalProductos; i++)
    {
        total += tiempos[i] * cantidades[i];
    }
    return total;
}

int calcularRecursosTotales(int *cantidades, int *recursos, int totalProductos)
{
    int total = 0;
    for (int i = 0; i < totalProductos; i++)
    {
        total += recursos[i] * cantidades[i];
    }
    return total;
}

void verificarDemanda(int *cantidades, int *tiempos, int *recursos, int totalProductos, int tiempoDisponible, int recursosDisponibles)
{
    if (totalProductos == 0)
    {
        printf("\nERROR: NO SE HAN INGRESADO PRODUCTOS\n");
        return;
    }
    int tiempoNecesario = calcularTiempoTotal(cantidades, tiempos, totalProductos);
    int recursosNecesarios = calcularRecursosTotales(cantidades, recursos, totalProductos);
    printf("\n--- RESULTADOS DE VERIFICACION ---\n");
    printf("Tiempo requerido: %d segundos\n", tiempoNecesario);
    printf("Recursos requeridos: %d unidades\n", recursosNecesarios);
    if (tiempoNecesario <= tiempoDisponible && recursosNecesarios <= recursosDisponibles)
    {
        printf("\n>>> CONCLUSION: La fabrica PUEDE cumplir con la demanda<<<<<\n");
    }
    else
    {
        printf("\nERROR: LA FABRICA NO PUEDE CUMPLIR LA DEMANDA\n");
    }
}
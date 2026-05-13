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

int compararNombres(char cad1[], char cad2[]) {
    for (int i = 0; cad1[i] != '\0' && cad2[i] != '\0'; i++) {
        char c1 = cad1[i];
        char c2 = cad2[i];
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
        
        if (c1 != c2) return 0;
    }
    return 1;
}

void ingresarProducto(char nombres[][MAX_NOMBRE], int *cantidades, int *tiempos, int *recursos, int *totalProductos)
{
    if (*totalProductos < MAX_PROD)
    {
        char nombreTemp[MAX_NOMBRE];
        printf("\n--------INGRESANDO NUEVO PRODUCTO------------\n ");
        printf("\nNombre del producto: ");
        printf("\n>>");
        fgets(nombreTemp, MAX_NOMBRE, stdin);
        limpiarSaltoDeLinea(nombreTemp);
        if (buscarProducto(nombres, *totalProductos, nombreTemp) != -1) {
            printf("\nERROR: ESE PRODUCTO YA EXISTE EN EL SISTEMA\n");
            return;
        }
        strcpy(nombres[*totalProductos], nombreTemp);
        printf("\nCantidad");
        printf("\n>>");
        cantidades[*totalProductos] = validacionentero(1, 9999999);
        printf("\nTiempo por unidad en minutos: ");
        printf("\n>>");
        tiempos[*totalProductos] = validacionentero(1, 9999999);
        printf("\n Materiales para usar en los productos por unidad: ");
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
        if (compararNombres(nombres[i], nombre) == 1)
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
        printf("\n¿Que dato desea editar de %s?\n", nombres[pos]);
        printf("1. Nombre\n2. Cantidad\n3. Tiempo por unidad\n4. Materiales por unidad\n>> ");
        int opcEditar = validacionentero(1, 4);

        if (opcEditar == 1) {
            char nuevoNombre[MAX_NOMBRE];
            printf("\nNuevo nombre: \n>>");
            fgets(nuevoNombre, MAX_NOMBRE, stdin);
            limpiarSaltoDeLinea(nuevoNombre);
            if (buscarProducto(nombres, totalProductos, nuevoNombre) != -1) {
                printf("\nERROR: ESE NOMBRE YA ESTA EN USO\n");
            } else {
                strcpy(nombres[pos], nuevoNombre);
                printf("Nombre actualizado.\n");
            }
        } else if (opcEditar == 2) {
            printf("\nNueva cantidad (actual: %d): ", cantidades[pos]);
            printf("\n>>");
            cantidades[pos] = validacionentero(1, 9999999);
        } else if (opcEditar == 3) {
            printf("\nNuevo tiempo por unidad en minutos (actual: %d): ", tiempos[pos]);
            printf("\n>>");
            tiempos[pos] = validacionentero(1, 9999999);
        } else if (opcEditar == 4) {
            printf("\nNuevos recursos por unidad (actual: %d): ", recursos[pos]);
            printf("\n>>");
            recursos[pos] = validacionentero(1, 9999999);
        }
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
        printf("\nERROR: NO HAY PRODUCTOS DISPONIBLES PARA ELIMINAR\n");
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
            strcpy(nombres[i], nombres[i+1]);

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

void gestionarDemandaYSock(char nombres[][MAX_NOMBRE], int *cantidades, int *tiempos, int *recursos, int totalProductos, int *tiempoDisponible, int *recursosDisponibles)
{
    printf("\n--- GESTION DE DEMANDA ---\n");
    printf("1. Verificar viabilidad (Ver si la fabrica cumple)\n");
    printf("2. Editar parametros de demanda\n");
    printf(">> ");
    int subopc = validacionentero(1, 2);

    if (subopc == 1) {
        verificarDemanda(nombres, cantidades, tiempos, recursos, totalProductos, *tiempoDisponible, *recursosDisponibles);
    } else {
        printf("\n¿Que desea editar?\n");
        printf("1. Editar el limite de tiempo disponible\n");
        printf("2. Editar las cantidades pedidas de un producto\n");
        printf("3. Hacer restock de materiales (sumar al inventario)\n");
        printf(">> ");
        int opcEditarD = validacionentero(1, 3);

        if (opcEditarD == 1) {
            printf("\nIngresar nuevo limite de tiempo disponible (minutos): ");
            *tiempoDisponible = validacionentero(0, 9999999);
            printf("! Tiempo actualizado con exito !\n");
        } 
        else if (opcEditarD == 2) {
            if (totalProductos == 0) {
                printf("\nERROR: NO HAY PRODUCTOS REGISTRADOS\n");
            } else {
                char nombreProd[MAX_NOMBRE];
                printf("\nNombre del producto para cambiar su cantidad pedida: \n>> ");
                fgets(nombreProd, MAX_NOMBRE, stdin);
                limpiarSaltoDeLinea(nombreProd);
                
                int pos = buscarProducto(nombres, totalProductos, nombreProd);
                if (pos != -1) {
                    printf("\nNueva cantidad de %s (actual: %d): \n>> ", nombres[pos], cantidades[pos]);
                    cantidades[pos] = validacionentero(1, 9999999);
                    printf("! Cantidad demandada actualizada !\n");
                } else {
                    printf("\nERROR: PRODUCTO NO ENCONTRADO\n");
                }
            }
        } 
        else if (opcEditarD == 3) {
            printf("\nIngresar recursos a sumar al inventario actual: ");
            *recursosDisponibles += validacionentero(0, 9999999);
            printf("! Stock de materiales actualizado !\n");
        }
    }
}

void verificarDemanda(char nombres[][MAX_NOMBRE], int *cantidades, int *tiempos, int *recursos, int totalProductos, int tiempoDisponible, int recursosDisponibles)
{
    if (totalProductos == 0)
    {
        printf("\nERROR: NO SE HAN INGRESADO PRODUCTOS\n");
        return;
    }
    printf("\n1. Demanda Global (Todos los productos)\n2. Demanda Especifica\n>> ");
    int opc = validacionentero(1, 2);
    int tiempoNecesario = 0, recursosNecesarios = 0;
    if (opc == 1) {
        tiempoNecesario = calcularTiempoTotal(cantidades, tiempos, totalProductos);
        recursosNecesarios = calcularRecursosTotales(cantidades, recursos, totalProductos);
        printf("\n--- RESULTADOS DE VERIFICACION GLOBAL ---\n");
    } else {
        char nombre[MAX_NOMBRE];
        printf("\nNombre del producto a calcular: \n>> ");
        fgets(nombre, MAX_NOMBRE, stdin);
        limpiarSaltoDeLinea(nombre);
        
        int pos = buscarProducto(nombres, totalProductos, nombre);
        if (pos == -1) {
            printf("\nERROR: PRODUCTO NO ENCONTRADO\n");
            return;
        }
        tiempoNecesario = tiempos[pos] * cantidades[pos];
        recursosNecesarios = recursos[pos] * cantidades[pos];
        printf("\n--- RESULTADOS PARA: %s ---\n", nombres[pos]);
    }
    printf("Tiempo requerido: %d min | Tiempo disponible: %d min\n", tiempoNecesario, tiempoDisponible);
    printf("Recursos requeridos: %d uni | Recursos disponibles: %d uni\n", recursosNecesarios, recursosDisponibles);
    int recursosRestantes = recursosDisponibles - recursosNecesarios;
    int tiempoRestante = tiempoDisponible - tiempoNecesario;
    if (tiempoRestante >= 0 && recursosRestantes >= 0)
    {
        printf("\n>>> CONCLUSION: La fabrica PUEDE cumplir con la demanda <<<<<\n");
        printf("Quedaran en stock: %d recursos y %d minutos.\n", recursosRestantes, tiempoRestante);
    }
    else
    {
        printf("\nERROR: LA FABRICA NO PUEDE CUMPLIR LA DEMANDA\n");
        if (recursosRestantes < 0) printf("Faltan %d recursos.\n", recursosRestantes * -1);
        if (tiempoRestante < 0) printf("Faltan %d minutos.\n", tiempoRestante * -1);
    }
}
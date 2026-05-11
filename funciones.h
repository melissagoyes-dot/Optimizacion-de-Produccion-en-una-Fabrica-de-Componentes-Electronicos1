#define MAX_PROD 5
#define MAX_NOMBRE 30

void ingresarProducto(char nombres[][MAX_NOMBRE], int *cantidades, int *tiempos, int *recursos, int *totalProductos);
int buscarProducto(char nombres[][MAX_NOMBRE], int totalProductos, char nombre[]);
void editarProducto(char nombres[][MAX_NOMBRE], int *cantidades, int *tiempos, int *recursos, int totalProductos);
void eliminarProducto(char nombres[][MAX_NOMBRE], int *cantidades, int *tiempos, int *recursos, int *totalProductos);
int calcularTiempoTotal(int *cantidades, int *tiempos, int totalProductos);
int calcularRecursosTotales(int *cantidades, int *recursos, int totalProductos);
void verificarDemanda(int *cantidades, int *tiempos, int *recursos, int totalProductos, int tiempoDisponible, int recursosDisponibles);
int validacionentero(int a, int b);
void limpiarSaltoDeLinea(char cadena[]);
void limpiarBuffer();
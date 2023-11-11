///Librerías
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <malloc.h>
#include <ctype.h>
#include <time.h>
#include "lista.h"

///Macros
#define DIM_CATEGORIAS 10
#define DIM 30

///Estructuras
typedef struct stArregloDeListas {

    int idCategoria;
    char nombreCategoria[DIM];
    stNodo *ptrListaProductos;

} stArregloDeListas;

/**------------------------------------------------------------------------------------------**/
int main(){

    /*Muestro el archivo para ver que datos contiene*/
    char nombreArchivo[] = {"registros.bin"};
    //mostrarArchivoRegistros(nombreArchivo);

    /*Declaro el ArregloDeCategorias de manera estática*/
    stArregloDeListas arregloDeCategorias[DIM_CATEGORIAS];
    int validosArregloCategorias = 0;

    /*DEBUG: Comprobar si se inicializó correctamente*/
    inicializarArregloDeListas(arregloDeCategorias);
    //mostrarArregloDeListas(arregloDeCategorias, validosArregloCategorias);

    /*Pasar del Archivo al ArregloDeListas*/
    cargarDatosDesdeArchivo(nombreArchivo, arregloDeCategorias, &validosArregloCategorias);
    mostrarArregloDeListas(arregloDeCategorias, validosArregloCategorias);

    /*Pasar una categoria en particular a un Archivo Binario*/
     char nombreArchivoCategoriaParticular[] = {"RegistroDeUnProducto.bin"};
     char categoria[] = {"bebidas"};
     cargarArchivoConCategoriaParticular(nombreArchivoCategoriaParticular, arregloDeCategorias, validosArregloCategorias, categoria);
     mostrarArchivoRegistros(nombreArchivoCategoriaParticular);
}
/**------------------------------------------------------------------------------------------**/
///Funciones

void mostrarArchivoRegistros(char nombreArchivo[]) {

    FILE *ptrArchivo = fopen(nombreArchivo, "rb");

    if(ptrArchivo == NULL) printf("\nError al abrir el Archivo\n");

    else {
        while(!feof(ptrArchivo)) {

            stRegistroProductos auxiliarRegistroProductos;
            fread(&auxiliarRegistroProductos, sizeof(stRegistroProductos), 1, ptrArchivo);

            if(!feof(ptrArchivo)) mostrarRegistroProductos(auxiliarRegistroProductos);
        }
     fclose(ptrArchivo);
    }
}

void mostrarRegistroProductos(stRegistroProductos auxiliarRegistroProductos) {

    printf("-----------------------------------------------------------\n");
    printf("Nombre Categoria: %s \n", auxiliarRegistroProductos.nombreCategoria);
    printf("ID Categoria: %i \n", auxiliarRegistroProductos.idCategoria);
    printf("ID Producto: %i \n", auxiliarRegistroProductos.idProducto);
    printf("Nombre Producto: %s \n", auxiliarRegistroProductos.nombreProducto);
    printf("Cantidad en Stock: %i \n", auxiliarRegistroProductos.cantidadStock);
    printf("Vencimiento: %s \n\n", auxiliarRegistroProductos.fechaExpiracion);
    printf("-----------------------------------------------------------\n");

}

void inicializarArregloDeListas(stArregloDeListas arregloDeCategorias[]) {

    for(int i = 0; i < DIM_CATEGORIAS; i++) {

        arregloDeCategorias[i].idCategoria = -1;
        strcpy(arregloDeCategorias[i].nombreCategoria, "");
        arregloDeCategorias[i].ptrListaProductos = inicLista();
    }
}

void mostrarListaProductos(stNodo *ptrListaProductos) {

    if(ptrListaProductos != NULL) {

        printf("Nombre Producto: %s \n", ptrListaProductos->infoProducto.nombreProducto);
        printf("ID Producto: %i \n", ptrListaProductos->infoProducto.idProducto);
        printf("Cantidad en Stock: %i \n", ptrListaProductos->infoProducto.cantidadStock);
        printf("Vencimiento: %s \n\n", ptrListaProductos->infoProducto.fechaExpiracion);

        mostrarListaProductos(ptrListaProductos->siguiente);
    }
}

void mostrarArregloDeListas(stArregloDeListas arregloDeCategorias[], int validos) {

    for(int i = 0; i < validos; i++) {

        printf("-----------------------------------------------------------\n");
        printf("ARREGLO EN LA POSICION: |%i| \n\n", i);
        printf("Nombre Categoria: %s \n", arregloDeCategorias[i].nombreCategoria);
        printf("ID Categoria: %i \n\n", arregloDeCategorias[i].idCategoria);

        if(arregloDeCategorias[i].ptrListaProductos == NULL) printf("La Lista esta vacia\n\n");

        else {
            printf("LISTA DE PRODUCTOS DE LA CATEGORIA: |%s| \n\n", arregloDeCategorias[i].nombreCategoria);

            mostrarListaProductos(arregloDeCategorias[i].ptrListaProductos);
            printf("-----------------------------------------------------------\n\n\n");
        }
    }
}

int buscarCategoria(stArregloDeListas arregloDeCategorias[], int validos, char nombreCategoriaBuscada[]) {

    for(int i = 0; i < validos; i++) if(strcmp(arregloDeCategorias[i].nombreCategoria, nombreCategoriaBuscada) == 0) return i;

    return -1;
}

void copiarInfoProducto(stRegistroProductos unRegistro, stProducto *informacionProducto) {

    strcpy(informacionProducto->nombreProducto, unRegistro.nombreProducto);
    informacionProducto->idProducto = unRegistro.idProducto;
    informacionProducto->cantidadStock = unRegistro.cantidadStock;
    strcpy(informacionProducto->fechaExpiracion, unRegistro.fechaExpiracion);
}

void crearCategoria(stArregloDeListas arregloDeCategorias[], int *validos, stRegistroProductos unRegistro) {

    if (*validos == DIM_CATEGORIAS) printf("ERROR: No hay mas espacio para almacenar una categoria nueva\n\n");

    else {
        int resultadoBusquedaCategoria = buscarCategoria(arregloDeCategorias, *validos, unRegistro.nombreCategoria);

        if (resultadoBusquedaCategoria != -1) {

            // La categoría ya existe, agregamos el producto a la lista de productos de la categoría
            stProducto informacionProducto;
            copiarInfoProducto(unRegistro, &informacionProducto);

            arregloDeCategorias[resultadoBusquedaCategoria].ptrListaProductos = agregarFinal(arregloDeCategorias[resultadoBusquedaCategoria].ptrListaProductos, crearNodo(informacionProducto));

        }else {

            // La categoría no existe, creamos la categoría y asignamos la información correspondiente
            strcpy(arregloDeCategorias[*validos].nombreCategoria, unRegistro.nombreCategoria);
            arregloDeCategorias[*validos].idCategoria = unRegistro.idCategoria;

            // Cargamos el producto a la lista
            stProducto informacionProducto;
            copiarInfoProducto(unRegistro, &informacionProducto);

            // Creamos un nodo y lo agregamos al final de la lista
            arregloDeCategorias[*validos].ptrListaProductos = agregarFinal(arregloDeCategorias[*validos].ptrListaProductos, crearNodo(informacionProducto));

            // Modificamos los validos originales
            *validos = *validos + 1;
        }
    }
}

void cargarDatosDesdeArchivo(char nombreArchivo[], stArregloDeListas arregloDeCategorias[], int *validos) {

    FILE *ptrArchivo = fopen(nombreArchivo, "rb");

    if(ptrArchivo == NULL) printf("Error al abrir el Archivo %s\n", nombreArchivo);

    else {

        while(!feof(ptrArchivo)) {

            stRegistroProductos unRegistro;
            fread(&unRegistro, sizeof(stRegistroProductos), 1, ptrArchivo);

            if(!feof(ptrArchivo)) crearCategoria(arregloDeCategorias, validos, unRegistro);
        }
        fclose(ptrArchivo);
    }
}

void cargarArchivoConCategoriaParticular(char nombreArchivo[], stArregloDeListas arregloDeCategorias[], int validos, char nombreCategoria[]) {

    FILE *ptrArchivo = fopen(nombreArchivo, "ab");

    if(ptrArchivo == NULL) printf("Error al abrir el Archivo %s\n", nombreArchivo);

    else {
        int busquedaCategoria = buscarCategoria(arregloDeCategorias, validos, nombreCategoria);

        if(busquedaCategoria != -1) {

            stRegistroProductos auxRegistro;

            stNodo *auxLista = arregloDeCategorias[busquedaCategoria].ptrListaProductos;

            while(auxLista != NULL) {

                strcpy(auxRegistro.nombreCategoria, arregloDeCategorias[busquedaCategoria].nombreCategoria);
                auxRegistro.idCategoria =  arregloDeCategorias[busquedaCategoria].idCategoria;
                strcpy(auxRegistro.nombreProducto, auxLista->infoProducto.nombreProducto);
                auxRegistro.idProducto = auxLista->infoProducto.idProducto;
                auxRegistro.cantidadStock = auxLista->infoProducto.cantidadStock;
                strcpy(auxRegistro.fechaExpiracion, auxLista->infoProducto.fechaExpiracion);
                auxLista = auxLista->siguiente;

                fwrite(&auxRegistro, sizeof(stRegistroProductos), 1, ptrArchivo);
            }

        }else printf("No existe registrada en sistema la Categoria a buscar \n\n");

        fclose(ptrArchivo);
    }
}

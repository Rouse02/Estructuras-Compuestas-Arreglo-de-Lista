#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int idCategoria;
    int idProducto;
    char nombreProducto[30];
    char nombreCategoria[30];
    int cantidadStock;
    char fechaExpiracion [11];
} stRegistroProductos;

typedef struct
{
    int idProducto;
    char nombreProducto[30];
    int cantidadStock;
    char fechaExpiracion [11];
} stProducto;

typedef struct
{
    stProducto infoProducto;
    struct stNodo* siguiente;
} stNodo;

stNodo * inicLista();
stNodo * crearNodo(stProducto dato);
stNodo * agregarFinal(stNodo * lista, stNodo * nuevoNodo);
void mostrarNodo(stNodo * aux);
void recorrerYmostrar(stNodo * lista);
stNodo * buscarUltimo(stNodo * lista);

#endif // LISTA_H_INCLUDED

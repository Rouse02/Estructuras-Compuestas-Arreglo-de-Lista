#include "lista.h"

stNodo * inicLista()
{
    return NULL;
}

stNodo * crearNodo(stProducto infoProducto)
{
    stNodo * aux = (stNodo*)malloc(sizeof(stNodo));
    aux->infoProducto = infoProducto;
    aux->siguiente = NULL;

    return aux;
}

stNodo * buscarUltimo(stNodo * lista)
{
    stNodo * seg = lista;
    if(seg != NULL)
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    return seg;
}

stNodo * agregarFinal(stNodo * lista, stNodo * nuevoNodo)
{

    if(lista == NULL) lista = nuevoNodo;

    else  {
        stNodo *ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevoNodo;
    }
    return lista;
}

void mostrarNodo(stNodo * aux)
{
    /** completar esta funcion **/
}

void recorrerYmostrar(stNodo * lista)
{
    stNodo * aux=lista;
    while(aux!=NULL)
    {
        mostrarNodo(aux);
        aux=aux->siguiente;
    }
}

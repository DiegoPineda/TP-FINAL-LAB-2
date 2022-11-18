#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loginYMenu.h"

typedef struct
{
    cliente dato;
    struct nodoArbol *izq;
    struct nodoArbol *der;
}nodoArbol;


nodoArbol *inicArbol();
nodoArbol *crearNodoArbol(cliente nvoCliente);
nodoArbol *insertar(nodoArbol *arbol, nodoArbol *nvoNodo);
nodoArbol *leerArvchivoClientes(nodoArbol *arbol);
void inorder(nodoArbol *arbol);
nodoArbol *busqueda(nodoArbol *arbol, char dni[]);
nodoArbol *bajaLogicaCliente(nodoArbol *arbol);
nodoArbol *modificarCliente(nodoArbol *arbol);
void modificarClienteEnArchivo(cliente a);
void mostrarUnCliente(nodoArbol * arbol);

#endif // ARBOL_H_INCLUDED

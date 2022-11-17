#include "loginYMenu.h"
#include "arbol.h"


nodoArbol *inicArbol()
{
    return NULL;
}

nodoArbol *crearNodoArbol(cliente nvoCliente)
{
    nodoArbol *nvoArbol= (nodoArbol*) malloc(sizeof(nodoArbol));
    nvoArbol->dato = nvoCliente;
    nvoArbol->der= NULL;
    nvoArbol->izq= NULL;
    return nvoArbol;
}

nodoArbol *insertar(nodoArbol *arbol, nodoArbol *nvoNodo)
{
    if(arbol == NULL)
    {
        arbol = nvoNodo;
    }
    else
    {
        if(strcmpi(nvoNodo->dato.dni, arbol->dato.dni) < 0)
        {
            arbol->der= insertar(arbol->der, nvoNodo);
        }
        else
        {
            arbol->izq= insertar(arbol->izq, nvoNodo);
        }
    }
    return arbol;
}

nodoArbol *leerArvchivoClientes(nodoArbol *arbol)
{
    cliente nvoCliente;
    nodoArbol *nvoNodo;
    FILE *buffer = fopen("usuarios.dat","rb");
    if(buffer != NULL)
    {
        while(fread(&nvoCliente, sizeof(cliente), 1, buffer)> 0)
        {
            nvoNodo = crearNodoArbol(nvoCliente);
            arbol = insertar (arbol, nvoNodo);
        }
        fclose(buffer);
    }
    return arbol;
}

void inorder(nodoArbol *arbol)
{
    if(arbol != NULL)
    {
        inorder(arbol->der);
        if(arbol->dato.baja == 0)
        {
            muestraUnUsuario(arbol->dato);
        }
        inorder(arbol->izq);
    }
}

nodoArbol *busqueda(nodoArbol *arbol, char dni[])
{
    nodoArbol *auxiliar =NULL;
    if(arbol != NULL)
    {
        if(strcmpi(arbol->dato.dni, dni) == 0)
        {
            auxiliar=arbol;
        }
        else
        {
            if(strcmpi(dni, arbol->dato.dni) >0)
            {
                auxiliar=busqueda(arbol->der, dni);
            }
            else
            {
                auxiliar=busqueda(arbol->izq, dni);
            }
        }
    }
    return auxiliar;
}

nodoArbol *bajaLogicaCliente(nodoArbol *arbol)
{
    printf("\n\tDAR DE BAJA UN CLIENTE\n");
    printf("Ingrese el DNI del cliente: ");
    fflush(stdin);
    char dni[10];
    gets(dni);
    nodoArbol *nodoBuscado = busqueda(arbol, dni);
    if(nodoBuscado != NULL)
    {
        nodoBuscado->dato.baja=1;
    }
    return arbol;
}

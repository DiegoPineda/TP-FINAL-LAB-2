#include <stdio.h>
#include <stdlib.h>
#include "string.h"

///Prototipado de funciones:
void menu();
nodoArb* inicArbol();
nodoArb* inicNodoArb();
nodoArb* crearNodoArb(persona dato);
nodoArb* insertarEnArb(nodoArb* arbol,nodoArb* nuevoNodo);
void mostrarPreOrder(nodoArb* arbol);
void mostrarInOrder(nodoArb* arbol);
void mostrarPostOrder(nodoArb* arbol);
nodoArb* buscarEnArbol(nodoArb* arbol,char dni[]);
char preguntar();
nodoArb* cargarArbol(nodoArb* arbol,int *cantidad);

///Cuerpo de funciones:

nodoArb* inicArbol()
{
    return NULL;
}

nodoArb* inicNodoArb()
{
    return NULL;
}

nodoArb* crearNodoArb(usuario dato)
{
    nodoArb* aux=(nodoArb*)malloc(sizeof(nodoArb));
    aux->dato=dato;
    aux->izq=inicNodoArb();
    aux->der=inicNodoArb();
    return aux;
}

nodoArb* insertarEnArb(nodoArb* arbol,nodoArb* nuevoNodo)
{
    if(arbol==NULL)
    {
        arbol=nuevoNodo;
    }
    else
    {
        if(nuevoNodo->dato.dni>arbol->dato.dni)
        {
            arbol->der=insertarEnArb(arbol->der,nuevoNodo);
        }
        else
        {
            arbol->izq=insertarEnArb(arbol->izq,nuevoNodo);
        }
    }
    return arbol;
}

void mostrarPreOrder(nodoArb* arbol)
{
    if(arbol!=NULL)
    {
        printf("Nombre: %s",arbol->dato.nombreYApellido);
        printf("\nDni: %s",arbol->dato.dni);
        printf("\nCalle y altura: %s",arbol->dato.calleYAltura);
        printf("\nTelefono: %s",arbol->dato.telefono);

        printf("\n--------------------\n");
        mostrarPreOrder(arbol->izq);
        mostrarPreOrder(arbol->der);
    }
}

void mostrarInOrder(nodoArb* arbol)
{
    if(arbol!=NULL)
    {
        mostrarInOrder(arbol->izq);
        printf("Nombre: %s",arbol->dato.nombreYApellido);
        printf("\nDni: %s",arbol->dato.dni);
        printf("\nCalle y altura: %s",arbol->dato.calleYAltura);
        printf("\nTelefono: %s",arbol->dato.telefono);
        printf("\n--------------------\n");
        mostrarInOrder(arbol->der);
    }
}

void mostrarPostOrder(nodoArb* arbol)
{
    if(arbol!=NULL)
    {
        mostrarPostOrder(arbol->izq);
        mostrarPostOrder(arbol->der);
        printf("Nombre: %s",arbol->dato.nombreYApellido);
        printf("\nDni: %s",arbol->dato.dni);
        printf("\nCalle y altura: %s",arbol->dato.calleYAltura);
        printf("\nTelefono: %s",arbol->dato.telefono);
        printf("\n--------------------\n");
    }
}

nodoArb* buscarEnArbol(nodoArb* arbol,int dni)
{
    nodoArb* rta=inicNodoArb();

    if(arbol!=NULL)
    {
        if(strcmp(dni,arbol->dato.dni)==0)
        {
            rta=arbol;
        }
        else
        {
            if(strcmp(dni,arbol->dato.dni)>0)
                rta=buscarEnArbol(arbol->der,dni);
            else
                rta=buscarEnArbol(arbol->izq,dni);
        }
    }
    return rta;
}

char preguntar()
{
    char control='s';

    system("cls");
    printf("Desea seguir?(S/N): ");
    fflush(stdin);
    scanf("%c",&control);
    system("cls");

    return control;
}

nodoArb* cargarArbol(nodoArb* arbol,int *cantidad)
{
    cliente a;
    nodoArb* aux;
    char control='s';

    while(control=='s')
    {
        printf("Nombre y apellido: ");
        fflush(stdin);
        gets(a.nombreYApellido);

        printf("Dni: ");
        fflush(stdin);
        gets(a.dni);

        printf("Calle y altura: ");
        fflush(stdin);
        gets(a.calleYAltura);

        printf("Telefono: ");
        fflush(stdin);
        gets(a.telefono);

        aux=crearNodoArb(a);
        arbol=insertarEnArb(arbol,aux);
        *cantidad=cantidad+1;
        control=preguntar();
    }
    return arbol;
}

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

///Prototipado de funciones:
void menu();
nodo* inicLista();
nodoArb* inicArbol();
nodoArb* inicNodoArb();
nodoArb* crearNodoArb(persona dato);
nodoArb* insertarEnArb(nodoArb* arbol,nodoArb* nuevoNodo);
void mostrarPreOrder(nodoArb* arbol);
void mostrarInOrder(nodoArb* arbol);
void mostrarPostOrder(nodoArb* arbol);
nodoArb* buscarEnArbol(nodoArb* arbol,int legajo);
char preguntar();
nodoArb* cargarArbol(nodoArb* arbol,int *cantidad);
int sumarLegajos(nodoArb* arbol);
nodo* crearNodoLista(persona dato);
nodo* agregarEnListaAlppio(nodo* lista,nodo* nuevoL);
nodo* pasarArbolALista(nodoArb* arbol,nodo* lista);
void mostrarListaRecursiva(nodo* lista);

int main()
{
    menu();

    return 0;
}

///Cuerpo de funciones:

void menu()
{
    int opc;
    nodoArb* arbol;
    nodoArb* nuevoNodo;
    persona dato;
    int legajo=0,sumaLegajos=0;
    int *cantidad=0;
    nodo* lista;
    nodo* nuevoL;
    nodo* buscado;

    system("cls");
    printf("Menu de la guia:\n\n");
    printf("\n[1]Ejercicio\n[2]Ejercicio\n[3]Ejercicio\n[4]Ejercicio\n[5]Ejercicio\n[6]Ejercicio\n[7]Ejercicio\n[8]Ejercicio\n[9]Ejercicio\n[10]Ejercicio");
    printf("\n\nSeleccione una opcion: ");
    scanf("%i",&opc);
    system("cls");
    switch(opc)
    {
    case 1:
        printf("Ejercicios 1 / 2 / 3:\n\n");
        lista=inicLista();
        arbol=inicArbol();
        arbol=cargarArbol(arbol,&cantidad);
        sumaLegajos=sumarLegajos(arbol);
        printf("La suma total de los legajos es: %i",sumaLegajos);
        printf("\n\n");
        system("pause");
        system("cls");
        printf("Su arbol en pre-orden:\n\n");
        mostrarPreOrder(arbol);
        printf("\n\n");
        system("pause");
        system("cls");
        printf("Su arbol en in-orden:\n\n");
        mostrarInOrder(arbol);
        printf("\n\n");
        system("pause");
        system("cls");
        printf("Su arbol en post-orden:\n\n");
        mostrarPostOrder(arbol);
        printf("\n\n");
        system("pause");
        system("cls");
        lista=pasarArbolALista(arbol,lista);
        printf("El contenido de su lista:\n\n");
        mostrarListaRecursiva(lista);
        printf("\n\n");
        system("pause");
        system("cls");
        printf("Ingrese el legajo de la persona que desea buscar!\n\n");
        printf("Legajo: ");
        scanf("%i",&legajo);
        system("cls");
        buscado=buscarEnArbol(arbol,legajo);
        if(buscado!=NULL)
        {
            printf("Se ha encontrado a la persona!\n\nSus datos son:\n\nNombre: %s\nLegajo: %i",buscado->dato.nombre,buscado->dato.legajo);
        }
        else
        {
            printf("No se ha encontrado a la persona!");
        }
        printf("\n\n");
        system("pause");
        system("cls");
        menu();
        break;
    }
}

nodo* inicLista()
{
    return NULL;
}

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
        printf("\nLegajo: %s",arbol->dato.dni);
        printf("\nCalle y altura: %s",arbol->dato.calleYAltura);
        printf("\nLegajo: %s",arbol->dato.telefono);

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
        printf("\nLegajo: %s",arbol->dato.dni);
        printf("\nCalle y altura: %s",arbol->dato.calleYAltura);
        printf("\nLegajo: %s",arbol->dato.telefono);
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
        printf("\nLegajo: %s",arbol->dato.dni);
        printf("\nCalle y altura: %s",arbol->dato.calleYAltura);
        printf("\nLegajo: %s",arbol->dato.telefono);
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


nodo* crearNodoLista(usuario dato)
{
    nodo* aux=(nodo*)malloc(sizeof(nodo));
    aux->dato=dato;
    aux->sig=NULL;

    return aux;
}

nodo* agregarEnListaAlppio(nodo* lista,nodo* nuevoL)
{
    if(lista==NULL)
    {
        lista=nuevoL;
    }
    else
    {
        nuevoL->sig=lista;
        lista=nuevoL;
    }
    return lista;
}



void mostrarListaRecursiva(nodo* lista)
{
    if(lista!=NULL)
    {
        printf("Nombre: %s",lista->dato.nombre);
        printf("\nLegajo: %i",lista->dato.legajo);
        printf("\n--------------------\n");
        mostrarListaRecursiva(lista->sig);
    }
}


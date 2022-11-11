#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "windows.h"

///Funciones multi-uso:
char preguntar()
{
    char control;
    system("cls");
    printf("Desea seguir?(S/N): ");
    fflush(stdin);
    scanf("%c",&control);
    system("cls");

    return control;
}
nodo2* inicLista()
{
    return NULL;
}
nodo2* crearNodo(jugador dato)
{
    nodo2* aux=(nodo2*)malloc(sizeof(nodo2));
    aux->dato=dato;
    aux->anterior=NULL;
    aux->siguiente=NULL;
    return aux;
}
nodo2* agregarPrincipio(nodo2* lista,nodo2* nuevoNodo)
{
    nuevoNodo->siguiente=lista;
    if(lista!=NULL)
    {
        lista->anterior=nuevoNodo;
    }
    return nuevoNodo;
}
nodo2* buscarUltimo(nodo2* lista)
{
    nodo2* rta=lista;
    if(lista!=NULL)
    {
        while(rta->siguiente!=NULL)
        {
            rta=rta->siguiente;
        }
    }
    return rta;
}
nodo2* agregarFinal(nodo2* lista,nodo2* nuevoNodo)
{
    nodo2* ultimo=NULL;
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        ultimo=buscarUltimo(lista);
        ultimo->siguiente=nuevoNodo;
        nuevoNodo->anterior=ultimo;
    }
    return lista;
}
nodo2* agregarEnOrden(nodo2* lista,nodo2* nuevoNodo)
{
    nodo2* seg;
    nodo2* ante;
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        if(nuevoNodo->dato.nivel<lista->dato.nivel)
        {
            lista=agregarPrincipio(lista,nuevoNodo);
        }
        else
        {
            seg=lista->siguiente;
            ante=lista;
        }
        ante->siguiente=nuevoNodo;
        nuevoNodo->anterior=ante;
        nuevoNodo->siguiente=seg;
        if(seg!=NULL)
        {
            seg->anterior=nuevoNodo;
        }
    }
    return lista;
}
void mostrarLista(nodo2* lista)
{
    nodo2* seguir=lista;

    printf("Lista de elementos:\n\n");
    while(seguir!=NULL)
    {
        printf("\nNombre: %s",seguir->dato.nombre);
        printf("\nNivel: %i",seguir->dato.nivel);
        printf("\n*********************");
        seguir=seguir->siguiente;
    }
}

///Funciones para el ejercicio 1:
nodo2* cargarLista(nodo2* lista)
{
    jugador aux;
    nodo2* aux2;
    char control='s';

    while(control=='s')
    {
        printf("Nombre del jugador: ");
        fflush(stdin);
        gets(aux.nombre);
        printf("Nivel: ");
        scanf("%i",&aux.nivel);
        aux2=crearNodo(aux);
        lista=agregarPrincipio(lista,aux2);
        control=preguntar();
    }
    return lista;
}
nodo2* borrarNodo(char nombre[20],nodo2* lista)
{
    nodo2* seg;
    nodo2* ante;
    nodo2* aux;

    if((lista!=NULL)&&(strcmp(nombre,lista->dato.nombre)==0))
    {
        aux=lista;
        lista=lista->siguiente;///lista es el segundo. el primer nodo es el segundo.
        if (lista!=NULL)
        {
            lista->anterior=NULL; ///el anterior del primero queda apuntando a nulo SOLO en el caso que la lista original tenga +1
        }
        free(aux);
    }
    else
    {
        seg=lista->siguiente; ///el primero ya quedo evaluado, avanzo solo
        ante = seg->anterior;
        while((seg!=NULL)&&(strcmp(nombre,seg->dato.nombre)!=0))
        {
            ante=seg;
            seg=seg->siguiente;
        }
        if(seg!=NULL)
        {
            ante->siguiente=seg->siguiente;
            if (seg->siguiente!=NULL)
            {
                aux=seg->siguiente;
                aux->anterior=ante;
            }
            free(seg);
        }
    }
    return lista;
}


///Funciones ejercicio 3:
void inicFila(fila* cola)
{
    cola->adelante=inicLista();
    cola->atras=inicLista();
}
void mostrarFila(fila* cola)
{
    nodo2* aux=cola->adelante;
    printf("\nAdelante-------------------------------------------------Atras\n\n");
    while(aux!=NULL)
    {
        printf("Nombre/Nivel: %s %i",aux->dato.nombre,aux->dato.nivel);
        printf(" |");
        aux=aux->siguiente;
    }
    printf("\n\nAdelante-------------------------------------------------Atras\n");
}

jugador extraerDeFila(fila* cola)
{
    jugador rta;
    nodo2* aux;
    nodo2* sig;

    if(cola->adelante==NULL)
    {
        aux=cola->adelante;
        sig=aux->siguiente;
        if(cola->adelante!=cola->atras)
        {
            sig->anterior=NULL;
        }
        else
        {
            cola->adelante=NULL;
        }
        cola->adelante=sig;
        rta=aux->dato;
        free(aux);
    }
    return rta;
}
void agregaFinal(fila* cola, nodo2* nuevoNodo)
{
    if(cola->adelante==NULL)
    {
        cola->adelante=nuevoNodo;
        cola->atras=nuevoNodo;
    }
    else
    {
        nodo2* aux=cola->atras;
        aux->siguiente=nuevoNodo;
        nuevoNodo->anterior=aux;
        cola->atras=nuevoNodo;
    }
}
void leerFila(fila* cola)
{
    jugador a;
    nodo2* aux;

    printf("Ingrese el nombre: ");
    fflush(stdin);
    gets(a.nombre);
    printf("Ingrese el nivel: ");
    scanf("%i",&a.nivel);
    aux=crearNodo(a);
    agregaFinal(cola,aux);
}

int filavacia(fila* cola)
{
    int rta=0;
    if(cola->adelante==NULL)
    {
        rta=1;
    }
    return rta;
}

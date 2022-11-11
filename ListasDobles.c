#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "windows.h"

///Estructuras para el manejo de listas dobles:
typedef struct
{
    char nombre[20];
    int nivel;
} usuario;

typedef struct
{
    usuario dato;
    struct nodo2* anterior;
    struct nodo2* siguiente;
} nodo2;

typedef struct
{
    struct nodo2* adelante;
    struct nodo2* atras;
} fila;

///Funcion administradora:
void menu();
///Funciones multi-uso:
nodo2* inicLista();
nodo2* crearNodo(jugador dato);
nodo2* agregarPrincipio(nodo2* lista,nodo2* nuevoNodo);
nodo2* buscarUltimo(nodo2* lista);
nodo2* agregarFinal(nodo2* lista,nodo2* nuevoNodo);
nodo2* agregarEnOrden(nodo2* lista,nodo2* nuevoNodo);
char preguntar();
void mostrarLista(nodo2* lista);
///Funciones para el ejercicio 1:
nodo2* cargarLista(nodo2* lista);
nodo2* borrarNodo(char nombre[20],nodo2* lista);
///Funciones para el ejercicio 2:
int listaCapicua(nodo2* lista2,nodo2* lista3);
///Funciones para el ejercicio 3:
void inicFila(fila* cola);
void mostrarFila(fila* cola);
void agregarPpioFila(fila* cola,nodo2* nuevoNodo);
jugador extraerDeFila(fila* cola);
void agregaFinal(fila* cola, nodo2* nuevoNodo);
void leerFila(fila* cola);
jugador bprimero(fila* cola);
int filavacia(fila* cola);

int main()
{
    menu();
    return 0;
}
///Funcion administrativa:
void menu()
{
    ///Variables multiuso:
    int opcion=0;
    nodo2* lista;
    nodo2* lista2;
    nodo2* lista3;
    ///Variables ejercicio 1:
    char nombre[20];
    ///Variables ejercicio 2:
    int capicua;
    ///Variables ejercicio 3:
    fila* cola;
    char control='s';
    jugador tope;

    system("cls");
    printf("Menu de Guia TP4.2:\n");
    printf("\n[1] Ejercicio.");
    printf("\n[2] Ejercicio.");
    printf("\n[3] Ejercicio.");
    printf("\n\nSeleccione una opcion: ");
    scanf("%i",&opcion);
    system("cls");
    switch(opcion)
    {
    case 1:
        lista=inicLista();
        lista=cargarLista(lista);
        system("color 0c");
        printf("Ingrese el nombre del jugador que desea borrar: ");
        fflush(stdin);
        gets(nombre);
        system("cls");
        lista=borrarNodo(nombre,lista);
        system("color 07");
        mostrarLista(lista);
        printf("\n\n");
        system("pause");
        system("cls");
        menu();
        break;
    case 2:
        lista=inicLista();
        lista2=inicLista();
        lista3=inicLista();
        lista=cargarLista(lista);
        lista3=lista;
        lista2=buscarUltimo(lista);
        capicua=listaCapicua(lista2,lista3);
        if(capicua==0)
        {
            printf("La lista es capicua");
        }
        else
        {
            printf("La lista no es capicua");
        }
        printf("\n\n");
        system("pause");
        system("cls");
        menu();
        break;
    case 3:
        inicFila(&cola);
        while(control=='s')
        {
            leerFila(&cola);
            control=preguntar();
        }
        if(filavacia(&cola)==0)
        {
            printf("La fila esta cargada\n\n");
        }
        else
        {
            printf("La fila esta vacia\n\n");
        }
        mostrarFila(&cola);
        tope=bprimero(&cola);
        printf("\n\nEl primero de la fila es %s",tope.nombre);
        printf("\n\n");
        system("pause");
        system("cls");
        menu();
        break;

    }
}
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

///Funciones ejercicio 2:
int listaCapicua(nodo2* lista2,nodo2* lista3)
{
    int i=0;

    if(lista2!=lista3)
    {
        if(lista2->dato.nivel==lista3->dato.nivel)
        {
            i=listaCapicua(lista2->anterior,lista3->siguiente);
        }
        else
        {
            i=1;
        }
    }

    return i;
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
void agregarPpioFila(fila* cola,nodo2* nuevoNodo)
{
    nodo2* seg;

    if(cola->adelante==NULL)
    {
        cola->adelante=nuevoNodo;
        cola->atras=nuevoNodo;
    }
    else
    {
        seg=cola->adelante; ///seg es el primero de la fila
        nuevoNodo->siguiente=seg; ///el siguiente del nuevo es el primero de la fila
        seg->anterior=nuevoNodo; ///el anterior de seg tambien es el nuevo nodo
        cola->adelante=nuevoNodo; /// el primero de la fila ahora es el nuevo y su siguiente es el anterior primero
    }
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
jugador bprimero(fila* cola)
{
    jugador rta;

    rta.nivel=-1;
    if(cola->adelante!=NULL)
    {
        nodo2* aux=cola->adelante;
        strcpy(rta.nombre,aux->dato.nombre);
        rta.nivel=aux->dato.nivel;
    }
    return rta;
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

#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

typedef struct
{
    char nombreYApellido[30];
    char dni[8];
    char calleYAltura[30];
    char telefono[15];
} cliente;

typedef struct
{
    cliente dato;
    int baja;
    int admin;
    struct nodoArbol * der;
    struct nodoArb * izq;
} nodoArb;

typedef struct
{
    int id;
    char nombre[20];
    float precio;
    int stock;
} comida;

typedef struct
{
    comida dato;
    struct nodo2* anterior;
    struct nodo2* siguiente;
} nodoComida;

typedef struct
{
    int id;
    char nombre[20];
    char marca[20];
    float precio;
    int stock;
    bool alcohol;
    char contenido[5];
} bebida;

typedef struct
{
    char nombre[30];
    float precio;
    bool alcohol;
    char contenido[5];
    int cantidad;
} pedidoBebida;

typedef struct
{
    bebida dato;
    struct nodo2* anterior;
    struct nodo2* siguiente;
} nodoBebida;

typedef struct
{
    int id;
    char nombre[20];
    float precio;
    int stock;
} postre;

typedef struct
{
    postre dato;
    struct nodo2* anterior;
    struct nodo2* siguiente;
} nodoPostre;

typedef struct{
    pedidoUsuario user;
    struct nodoPedido *listaPedidos;
    struct pedidoCelda *sig;
}pedidoCelda;

typedef struct{
    int dni;
    int idpedido;
    float costeTotal;
}pedidoUsuario;

typedef struct{
    pedido p;
    struct nodoPedido *sig;
}nodoPedido;

typedef struct{
    char producto[30];
    int cantidad;
    float precio;
}pedido;

#endif

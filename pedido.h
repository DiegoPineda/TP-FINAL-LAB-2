#ifndef PEDIDO_H_INCLUDED
#define PEDIDO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comida.h"


typedef struct{
    char producto[30];
    int cantidad;
    float precio;
}pedido;

typedef struct{
    pedido p;
    struct nodoPedido *sig;
    struct nodoPedido *ante;
}nodoPedido;

typedef struct{
    char dni[10];
    int idpedido;
    float costeTotal;
}pedidoUsuario;

typedef struct{
    pedidoUsuario user;
    struct nodoPedido *listaPedidos;
    struct pedidoCelda *sig;
    struct pedidoCelda *ante;
}pedidoCelda;

typedef struct{
    char dni[10];
    int idpedido;
    float costeTotal;
    char producto[30];
    int cantidad;
    float precio;
}registroPedido;

pedidoCelda *leerPedidos(pedidoCelda *listaCeldas);
nodoPedido *crearNodoPedido(char producto[],int cantidad, float precio);
pedidoCelda *altaPedidos (pedidoCelda *listaCeldas, registroPedido aux);
pedidoCelda *buscarPosCelda(pedidoCelda *listaCeldas, int idPedido);
pedidoUsuario ingresarUsuarioPedido(char dni[],int idpedido, float costeTotal);
pedidoCelda *crearCeldaPedido(pedidoUsuario usuario);
pedidoCelda *inicListaCelda();
nodoPedido *inicListaPedidos();
pedidoCelda *agregarPpioCeldaPedido(pedidoCelda *lista,pedidoCelda *pos);
nodoPedido *agregarFinalPedidos(nodoPedido *lista,nodoPedido *nuevoNodo);
nodoPedido *buscarUltimoPedido (nodoPedido *lista);
void *hacerPedido(CatComida arreglo[],  int validos);
void mostrarListaPedidos(pedidoCelda *lista);
void mostrarItemPedidos(pedido *pedido);
pedidoCelda *BuscarPedidoPorDNI(pedidoCelda *pedidos, char dni[]);
pedidoCelda *borrarNodoPedido(pedidoCelda *lista, int id);
nodoPedido *borrarNodoProducto(nodoPedido *lista, char nombre[]);
pedidoCelda *borrarUNpedido(pedidoCelda *lista, char dni[]);

void *subirPedido(int idpedido);
void subirPedidoAux(nodoPedido *lista,int idpedido,float costeTotal);

#endif // PEDIDOS_H_INCLUDED




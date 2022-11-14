#include <stdio.h>
#include <stdlib.h>
#include <headers.h>
#include <listasDobles.h>
const char *archivoPedidos="pedidos.bin";

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
    char dni;
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
    char dni;
    int idpedido;
    float costeTotal;
    char producto[30];
    int cantidad;
    float precio;
}registroPedido;

int Npedidos;


pedidoCelda *leerPedidos(pedidoCelda *listaCeldas);
nodoPedido *crearNodoPedido(char producto[],int cantidad, float precio);
pedidoCelda *altaPedidos (pedidoCelda *listaCeldas, registroPedido *aux);
pedidoCelda *buscarPosCelda(pedidoCelda *listaCeldas, int idPedido);
pedidoUsuario ingresarUsuarioPedido(char dni[],int idpedido, float costeTotal);
pedidoCelda *crearCeldaPedido(pedidoUsuario usuario);
pedidoCelda *inicListaCelda();
nodoPedido *inicListaPedidos();
pedidoCelda *agregarPpioCeldaPedido(pedidoCelda *lista,pedidoCelda *pos);
nodoPedido *agregarFinalPedidos(nodoPedido *lista,nodoPedido *nuevoNodo);
nodoPedido *buscarUltimoPedido (nodoPedido *lista);



int main()
{

}


pedidoCelda *leerPedidos(pedidoCelda *listaCeldas)
{
    FILE *buffer=fopen(archivoPedidos,"rb");
    registroPedido *aux;
    if (buffer!=NULL)
    {
        while(fread(&aux,sizeof(registroPedido),1,buffer)>0)
        {
            Npedidos+=1;
            listaCeldas=altaPedidos(listaCeldas,aux);
        }
        fclose(buffer);
    }
    return listaCeldas;
}

pedidoCelda *altaPedidos (pedidoCelda *listaCeldas, registroPedido *aux) ///hacer una funcion que nos de un registropedido y ahi hacer el pedido++
{
    nodoPedido *nuevoNodo=crearNodoPedido(aux->producto,aux->cantidad,aux->precio);
    pedidoCelda *pos=buscarPosCelda(listaCeldas,aux->idpedido);
    if(pos==NULL)
    {
        pedidoUsuario c=ingresarUsuarioPedido(aux->dni,aux->idpedido,aux->costeTotal);
        pos=crearCeldaPedido(c);
        listaCeldas=agregarPpioCeldaPedido(listaCeldas,pos);
    }
    pos->listaPedidos=agregarFinalPedidos(pos->listaPedidos,nuevoNodo);
    return listaCeldas;
}

nodoPedido *crearNodoPedido(char producto[],int cantidad, float precio)
{
    nodoPedido *aux=(nodoPedido*)malloc(sizeof(nodoPedido));
    strcpy(aux->p.producto,producto);
    aux->p.cantidad=cantidad;
    aux->p.precio=precio;
    return aux;
}


pedidoCelda *buscarPosCelda(pedidoCelda *listaCeldas, int idPedido)
{
    pedidoCelda *pos=NULL;
    int flag=0;
    while (listaCeldas!=NULL && flag==0)
    {
        if(listaCeldas->user.idpedido == idPedido)
        {
            pos=listaCeldas;
            flag=1;
        }
        listaCeldas=listaCeldas->sig;
    }
    return pos;
}

pedidoUsuario ingresarUsuarioPedido(char dni[],int idpedido, float costeTotal)
{
    pedidoUsuario aux;
    strcpy(aux.dni,dni);
    aux.idpedido=idpedido;
    aux.costeTotal=costeTotal;
    return aux;
}

pedidoCelda *crearCeldaPedido(pedidoUsuario usuario)
{
    pedidoCelda *aux;
    aux->user=usuario;
    aux->listaPedidos=inicListaPedidos(); ///////////
    aux->sig=NULL;
    aux->ante=NULL;
    return aux;
}

pedidoCelda *inicListaCelda()
{
    return NULL;
}

nodoPedido *inicListaPedidos()
{
    return NULL;
}

pedidoCelda *agregarPpioCeldaPedido(pedidoCelda *lista,pedidoCelda *pos)
{
    if(lista==NULL)
    {
        lista=pos;
    }else
    {
        pos->sig=lista;
        lista->ante=pos;
        lista=pos;
    }
    return lista;
}

nodoPedido *agregarFinalPedidos(nodoPedido *lista,nodoPedido *nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }else
    {
        nodoPedido *ultimo=buscarUltimoPedido(lista);
        ultimo->sig=nuevoNodo;
        nuevoNodo->ante=ultimo;
    }
    return lista;
}

nodoPedido *buscarUltimoPedido (nodoPedido *lista)
{
    nodoPedido *seg=lista;
    if(seg!=NULL)
    {
        while (seg->sig!=NULL)
        {
            seg=seg->sig;
        }
    }
    return seg;
}
//
//registroPedido hacerPedido() ///hacer una funcion que nos de un registropedido y ahi hacer el pedido++
//{
//    registroPedido aux=NULL;
//
//
//
//}

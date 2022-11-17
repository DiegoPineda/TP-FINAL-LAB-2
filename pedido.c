#include "comida.h"
#include "pedido.h"


int Npedidos=1;

pedidoCelda *leerPedidos(pedidoCelda *listaCeldas)
{
    FILE *buffer=fopen("pedidos.bin","rb");
    registroPedido aux;
    if (buffer!=NULL)
    {
        while(fread(&aux,sizeof(registroPedido),1,buffer)>0)
        {
            listaCeldas=altaPedidos(listaCeldas,aux);
            Npedidos+=1;

        }
        fclose(buffer);
    }
    return listaCeldas;
}

pedidoCelda *altaPedidos (pedidoCelda *listaCeldas, registroPedido aux) ///hacer una funcion que nos de un registropedido y ahi hacer el pedido++
{
    nodoPedido *nuevoNodo=crearNodoPedido(aux.producto,aux.cantidad,aux.precio);
    pedidoCelda *pos=buscarPosCelda(listaCeldas,aux.idpedido);
    if(pos==NULL)
    {
        pedidoUsuario c=ingresarUsuarioPedido(aux.dni,aux.idpedido,aux.costeTotal);
        pos=crearCeldaPedido(c);
        listaCeldas=agregarPpioCeldaPedido(listaCeldas,pos);
    }
    pos->listaPedidos=agregarFinalPedidos(pos->listaPedidos,nuevoNodo);
    pos->user.costeTotal+=(nuevoNodo->p.precio)*(nuevoNodo->p.cantidad);
    return listaCeldas;
}

nodoPedido *crearNodoPedido(char producto[],int cantidad, float precio)
{
    nodoPedido *aux=(nodoPedido*)malloc(sizeof(nodoPedido));
    strcpy(aux->p.producto,producto);
    aux->p.cantidad=cantidad;
    aux->p.precio=precio;
    aux->sig=NULL;
    aux->ante=NULL;
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
    pedidoCelda *aux=(pedidoCelda*)malloc(sizeof(pedidoCelda));
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

pedidoCelda *hacerPedido(CatComida arreglo[],  int validos,pedidoCelda *lista) ///hacer una funcion que nos de un registropedido y ahi hacer el pedido++
{
    int elecc;
    int cate;
    registroPedido aux;
    strcpy(aux.dni,"40885253"); ///aca va la Variable global
    Npedidos++;
    aux.idpedido=Npedidos; ///no olvidar el ++
    aux.costeTotal=0;
    nodoComida *elegir;
    int pos;

    do
    {

        printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,187);
        printf("\n\t\t\t\t%cCARRITO%c",186,186);
        printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,188);
        printf("1.Ingresar producto\n2.Modificar producto\n3.Eliminar producto\n9.Realizar pedido\n0.Salir\n");
        fflush(stdin);
        scanf("%i",&elecc);

        switch(elecc)
        {
        case 1:
        {
            do
            {
                mostrarCategorias(arreglo,validos);
                printf("Ingrese el id de la categoria:\n ");
                fflush(stdin);
                scanf("%i",&cate);
                system("cls");
                pos=buscarPosCatComida(arreglo, cate, validos);
                printf("pos %i\n",pos);
                if(pos==-1)
                {
                    printf("Categoria incorrecta, intente otra vez\n");
                }
            }
            while(pos==-1);
            system("cls");
            mostrarListaComida(arreglo[pos].lista);
            int IdElegido;
            do
            {
                printf("Seleccione el id del producto:\n");
                fflush(stdin);
                scanf("%i",&IdElegido);
                elegir=encontrarComida(arreglo[pos].lista,IdElegido);
                if(elegir==NULL)
                {
                    printf("Id invalido, seleccione otro\n");
                }
            }
            while(elegir==NULL);


            strcpy(aux.producto,elegir->dato.nombre);
            printf("Ingrese la cantidad: \n");
            fflush(stdin);
            scanf("%i",&aux.cantidad);
            aux.precio=elegir->dato.precio;
            lista=altaPedidos(lista,aux);
            system("cls");
            mostrarUnPedido(lista,aux.idpedido);
            break;
        }
        case 2:
        {
            printf("Modificar\n");
            break;
        }
        case 3:
        {
            printf("Eliminar\n");
            break;
        }
        case 9:
        {
            printf("Subir a archivo\n");
            break;
        }
        case 0:
        {
            printf("Salir\n");
            break;
        }
        default:
        {
            printf("Error\n");
            break;
        }
        }

    }while(elecc!=9 && elecc!=0);


    return lista;
}

void mostrarListaPedidos(pedidoCelda *lista)
{
    while(lista!=NULL)
    {
        printf("DNI: %s\n",lista->user.dni);
        printf("ID Pedido: %i\n",lista->user.idpedido);
        mostrarListaItems(lista->listaPedidos);
        printf("Coste Total: %.2f\n",lista->user.costeTotal);
        lista=lista->sig;
    }
}

void mostrarListaItems(nodoPedido *lista)
{
    int i=1;

    while(lista!=NULL)
    {
        printf("%i. ",i);
        mostrarItem(lista->p);
        lista=lista->sig;
        i++;
    }
}

void mostrarItem(pedido p)
{
        printf("%s\n",p.producto);
        printf("%i x ",p.cantidad);
        printf("%.2f\n\n",p.precio);
}

void mostrarUnPedido(pedidoCelda *lista,int idpedido)
{
    while(lista->user.idpedido!=idpedido && lista!=NULL)
    {
        lista=lista->sig;
    }
    printf("DNI: %s\nID Pedido: %i\n",lista->user.dni,lista->user.idpedido);
    mostrarListaItems(lista->listaPedidos);
}



pedidoCelda *BuscarPedidoPorDNI(pedidoCelda *pedidos, char dni[])
{
    pedidoCelda *nodoBuscado = NULL;
    int flag=0;
    while(pedidos != NULL && flag == 0)
    {
        if(strcmpi(pedidos->user.dni, dni) ==0);
        {
            nodoBuscado=pedidos;
            flag=1;
        }
        pedidos= pedidos->sig;
    }
    return nodoBuscado;
}

pedidoCelda *borrarNodoPedido(pedidoCelda *lista, int id)
{
    if (lista != NULL)
    {
        if(lista->user.idpedido == id)
        {
            pedidoCelda *aBorrar = lista;
            lista = lista->sig;
            if(lista != NULL)
            {
                lista->ante = NULL;
            }
            free(aBorrar);
        }
        else
        {
            pedidoCelda *seguidora = lista;
            while(seguidora != NULL && seguidora->user.idpedido != id)
            {
                seguidora=seguidora->sig;
            }
            if(seguidora!= NULL)
            {
                pedidoCelda *anterior = seguidora->ante;
                anterior->sig = seguidora->sig;
                if(seguidora->sig != NULL)
                {
                    pedidoCelda *seg = seguidora->sig;
                    seg =  anterior;
                }
                free(seguidora);
            }
        }
    }
    return lista;
}

nodoPedido *borrarNodoProducto(nodoPedido *lista, char nombre[])
{
    if (lista != NULL)
    {
        if(strcmpi(lista->p.producto, nombre) == 0)
        {
            nodoPedido *aBorrar = lista;
            lista = lista->sig;
            if(lista != NULL)
            {
                lista->ante = NULL;
            }
            free(aBorrar);
        }
        else
        {
            nodoPedido *seguidora = lista;
            while(seguidora != NULL && strcmpi(seguidora->p.producto, nombre) !=0)
            {
                seguidora=seguidora->sig;
            }
            if(seguidora!= NULL)
            {
                nodoPedido *anterior = seguidora->ante;
                anterior->sig = seguidora->sig;
                if(seguidora->sig != NULL)
                {
                    nodoPedido *seg = seguidora->sig;
                    seg =  anterior;
                }
                free(seguidora);
            }
        }
    }
    return lista;
}


pedidoCelda *borrarUNpedido(pedidoCelda *lista, char dni[])
{
    char continuar='s';
    char nombreProducto[20];
    pedidoCelda *pedidoBuscado = BuscarPedidoPorDNI(lista, dni);

    printf("\tCANCELAR UN PRODUCTO\n");
    mostrarUnPedido(pedidoBuscado, pedidoBuscado->user.idpedido);
    printf("ingrese el nombre del producto: ");
    fflush(stdin);
    gets(nombreProducto);
    nodoPedido *productos = pedidoBuscado->listaPedidos;
    if(productos != NULL)
    {
        pedidoBuscado->listaPedidos = borrarNodoProducto(pedidoBuscado->listaPedidos, nombreProducto);
    }

    if(pedidoBuscado->listaPedidos == NULL)
    {

        int idPedido = pedidoBuscado->user.idpedido;
        lista = borrarNodoPedido(lista, idPedido);
    }

    return lista;
}



#include "comida.h"
#include "bebidas.h"
#include "postres.h"
#include "pedido.h"
#include "loginYMenu.h"
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
    pedidoCelda *seg=listaCeldas;
    int flag=0;
    while (seg!=NULL && flag==0)
    {
        if(seg->user.idpedido == idPedido)
        {
            pos=seg;
            flag=1;
        }
        seg=seg->sig;
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

void *hacerPedido(CatComida arreglo[],CeldaBebida CategoriasBeb[],CeldaPostre Categoriaspos[],  int validos,int validosBebida,int validosPostre) ///hacer una funcion que nos de un registropedido y ahi hacer el pedido++
{
    int elecc=0;
    int cate;
    registroPedido aux;
    strcpy(aux.dni,usuarioLogeado.dni); ///aca va la Variable global
    aux.idpedido=Npedidos; ///no olvidar el ++
    aux.costeTotal=0;
    nodoComida *elegir;
    nodoBebida *elegir2;
    nodoPostre *elegir3;
    int pos;

    do
    {

        printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,187);
        printf("\n\t\t\t\t%cCARRITO%c",186,186);
        printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,188);
        printf("1.Ingresar producto\n2.Modificar producto\n3.Eliminar producto\n9.Realizar pedido\n0.Salir\n");
        fflush(stdin);
        scanf("%i",&elecc);
        int tipo=0;

        switch(elecc)
        {
        case 1:
        {
            do
            {
                printf("1.Comida\n2.Bebidas\n3.Postres\n");
                fflush(stdin);
                scanf("%i",&tipo);
                if(tipo==1)
                {
                    mostrarCategorias(arreglo,validos);
                }else if(tipo==2)
                {
                    mostrarCategoriasBebidas(CategoriasBeb,validosBebida);
                }else if(tipo==3)
                {
                    mostrarCategoriasPostres(Categoriaspos,validosPostre);
                }
                printf("Ingrese el id de la categoria:\n ");
                fflush(stdin);
                scanf("%i",&cate);
                system("cls");
                if(tipo==1)
                {
                    pos=buscarPosCatComida(arreglo, cate, validos);
                }else if(tipo==2)
                {
                    pos=buscarPosCatBebida(CategoriasBeb,cate,validosBebida);
                }else if(tipo==3)
                {
                    pos=buscarPosCatPostre(Categoriaspos,cate,validosPostre);
                }

                printf("pos %i\n",pos);
                if(pos==-1)
                {
                    printf("Categoria incorrecta, intente otra vez\n");
                }
            }
            while(pos==-1);
            system("cls");
            if(tipo==1)
                {
                    mostrarListaComida(arreglo[pos].lista);
                }else if(tipo==2)
                {
                    mostrarListaBebida(CategoriasBeb[pos].lista);
                }else if(tipo==3)
                {
                    mostrarListaPostres(Categoriaspos[pos].lista);
                }

            int IdElegido;
            do
            {
                    printf("Seleccione el id del producto:\n");
                    fflush(stdin);
                    scanf("%i",&IdElegido);
                    if(tipo==1)
                    {

                        elegir=encontrarComida(arreglo[pos].lista,IdElegido);
                        if(elegir==NULL)
                        {
                            printf("Id invalido, seleccione otro\n");
                        }
                    }
                    else if(tipo==2)
                    {

                        elegir2=encontrarBebida(CategoriasBeb[pos].lista,IdElegido);
                        if(elegir2==NULL)
                        {
                            printf("Id invalido, seleccione otro\n");
                        }
                    }
                    else if(tipo==3)
                    {

                        elegir3=encontrarPostre(Categoriaspos[pos].lista,IdElegido);
                        if(elegir3==NULL)
                        {
                            printf("Id invalido, seleccione otro\n");
                        }
                    }


            }while(elegir==NULL && elegir2==NULL && elegir3==NULL);
            if(tipo==1)
                {
                    strcpy(aux.producto,elegir->dato.nombre);
                    aux.precio=elegir->dato.precio;
                }else if(tipo==2)
                {
                    strcpy(aux.producto,elegir2->dato.nombre);
                    aux.precio=elegir2->dato.precio;
                }else if(tipo==3)
                {
                    strcpy(aux.producto,elegir3->dato.nombre);
                    aux.precio=elegir3->dato.precio;
                }


            printf("Ingrese la cantidad: \n");
            fflush(stdin);
            scanf("%i",&aux.cantidad);
            printf("ID: %i   DNI: %s",aux.idpedido,aux.dni);
            listaPedidoCelda=altaPedidos(listaPedidoCelda,aux);
            system("cls");

            mostrarUnPedido(listaPedidoCelda,aux.idpedido);
            break;
        }
        case 9:
        {


            Npedidos=Npedidos+1;
            subirPedido(aux.idpedido);

            printf("Subir a archivo\n");
            system("pause");
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

}

void subirPedido(int idpedido)
{
    pedidoCelda *aux=listaPedidoCelda;
        while(aux->user.idpedido!=idpedido)
        {
            aux->sig;
        }
    subirPedidoAux(aux->listaPedidos,idpedido,aux->user.costeTotal);
}

void subirPedidoAux(nodoPedido *lista,int idpedido,float costeTotal)
{
    FILE *buffer=fopen("pedidos.bin","ab");
    registroPedido aux;
    strcpy(aux.dni,usuarioLogeado.dni);
    aux.idpedido=idpedido;
    aux.costeTotal=costeTotal;
    nodoPedido *aux2=lista;
    if(buffer!=NULL)
    {
        while(aux2!=NULL)
        {
            strcpy(aux.producto,aux2->p.producto);
            aux.cantidad=aux2->p.cantidad;
            aux.precio=aux2->p.cantidad;
            fwrite(&aux,sizeof(registroPedido),1,buffer);
            aux2=aux2->sig;
        }
        fclose(buffer);

    }

}




void mostrarListaPedidos(pedidoCelda *lista)
{
    while(lista!=NULL)
    {
        printf("___________________________________________\n");
        printf("DNI: %s\n",lista->user.dni);
        printf("ID Pedido: %i\n\n",lista->user.idpedido);
        mostrarListaItems(lista->listaPedidos);
        printf("Coste Total: %.2f\n",lista->user.costeTotal);
        printf("___________________________________________\n");
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
    pedidoCelda *aux=lista;
    while(aux->user.idpedido!=idpedido && aux!=NULL)
    {
        aux=aux->sig;
    }
    printf("DNI: %s\nID Pedido: %i\n",aux->user.dni,aux->user.idpedido);
    mostrarListaItems(aux->listaPedidos);
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




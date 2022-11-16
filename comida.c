#include "comida.h"
#include "pedido.h"

int menuComidas(CatComida arreglo[], int validos)
{
    int elecc;
    do
    {


        printf("1.Mostrar Categorias y Comidas\n2.Ingresar Nueva Comida\n3.Ingresar Nueva Categoria\n4.Cambiar Precio Comida\n5. Borrar una Comida\n6. Cambiar Precio Una Categoria.\n0.Salir\n");
        fflush(stdin);
        scanf("%i",&elecc);
        switch(elecc)
        {
        case 1:
        {
            mostrarArregloComidas(arreglo,validos);
            break;
        }
        case 2:
        {
            validos = ingresarNvaComida(arreglo,validos);
            break;
        }
        case 3:
        {
            validos = ingresarNvaCategria(arreglo, validos, 10);
            break;
        }
        case 4:
        {
            cambiarPrecioComida(arreglo, validos);
            break;
        }
        case 5:
        {
            BorrarUnaComida(arreglo, validos);
            break;
        }
        case 6:
        {
            cambiarPrecioUnaCategoria(arreglo, validos);
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

    }
    while(elecc!=0);


    return validos;
}

void mostrarArchiComidas()
{
    stDatosComida aux;
    FILE*archi=fopen("ArchivoComidas.bin","rb");
    if(archi!=NULL)
    {

        while(fread(&aux,sizeof(stDatosComida),1,archi)>0)
        {
            mostrarArchivo(aux);

        }
        fclose(archi);
    }
}

void mostrarArchivo(stDatosComida aux)
{
    printf("ID %d\n",aux.id);
    printf("NOMBRE %s\n",aux.nombre);
    printf("PRECIO %.2f\n",aux.precio);
    printf("id categoria %i\n",aux.id_categoria);
    printf("Nombre categoria %s\n",aux.nombre_cat);
    printf("--------------------------------------------------------------------------------------------\n");
    printf("\n");
}

void cargarArchivo1()
{
    stDatosComida auxiliar;
    FILE *buffer = fopen("ArchivoComidas.bin", "ab");
    if(buffer != NULL)
    {
        char continuar = 's';
        while(continuar == 's')
        {
            auxiliar = cargarStruct();
            fwrite(&auxiliar, sizeof(stDatosComida), 1, buffer);
            printf("Desea continuar? presione s\n");
            fflush(stdin);
            scanf("%c", &continuar);
            system("CLS");
        }

        fclose(buffer);
    }
}

void cargarArchivo(stDatosComida auxiliar)
{

    FILE *buffer = fopen("ArchivoComidas.bin", "ab");
    if(buffer != NULL)
    {
        fwrite(&auxiliar, sizeof(stDatosComida), 1, buffer);

        fclose(buffer);
    }
}

stDatosComida cargarStruct()
{
    printf("\t\t CARGA DE NUEVA COMIDA\n");
    stDatosComida auxiliar;
    printf("Ingrese el nombre de la categoria: \n");
    fflush(stdin);
    gets(auxiliar.nombre_cat);
    printf("Ingrese la id de la categoria: \n");
    fflush(stdin);
    scanf("%i", &auxiliar.id_categoria);
    printf("Ingrese el nombre de la comida: \n");
    fflush(stdin);
    gets(auxiliar.nombre);
    printf("Ingrese la id de la comida: \n");
    fflush(stdin);
    scanf("%i", &auxiliar.id);
    printf("Ingrese el precio de la comida: \n");
    fflush(stdin);
    scanf("%f", &auxiliar.precio);

    return auxiliar;

}

nodoComida *inicLista()
{
    return NULL;
}

nodoComida *crearNodo(comida dato)
{
    nodoComida *aux=(nodoComida*) malloc(sizeof(nodoComida));
    aux->dato = dato;
    aux->anterior = NULL;
    aux->siguiente = NULL;
    return aux;
}

nodoComida *agregarAlPrincipio(nodoComida *lista, nodoComida *nvoNodo)
{
    if(lista == NULL)
    {
        lista = nvoNodo;
    }
    else
    {
        lista->anterior = nvoNodo;
        nvoNodo->siguiente = lista;
        lista = nvoNodo;
    }
    return lista;
}

nodoComida *agregarOrdenado(nodoComida *lista, nodoComida *nvoNodo)
{
    if(lista == NULL)
    {
        lista = nvoNodo;
    }
    else
    {
        if(nvoNodo->dato.id < lista->dato.id)
        {
            lista = agregarAlPrincipio(lista, nvoNodo);
        }
        else
        {
            nodoComida *anterior = lista;
            nodoComida *seguidora = lista->siguiente;
            while(seguidora != NULL && nvoNodo->dato.id > seguidora->dato.id)
            {
                anterior = seguidora;
                seguidora = seguidora->siguiente;
            }
            anterior->siguiente = nvoNodo;
            nvoNodo->anterior = anterior;
            nvoNodo->siguiente = seguidora;
            if(seguidora != NULL)
            {
                seguidora->anterior = nvoNodo;
            }
        }
    }
    return lista;
}

int leerArvchivoComidas(CatComida arreglo[], int dimension)
{
    int validos =0;
    FILE *buffer = fopen("ArchivoComidas.bin", "rb");
    stDatosComida datosComida;
    if(buffer != NULL)
    {
        while(fread(&datosComida, sizeof(stDatosComida), 1, buffer) > 0 && validos < dimension)
        {
            validos = altaComidas(arreglo, datosComida, validos);
        }
        fclose(buffer);
    }

    return validos;
}

int buscarPosCatComida(CatComida arreglo[], int id, int validos)
{
    int rta =-1;
    int i=0;
    while(i<validos && rta == -1)
    {
        if(arreglo[i].dato.id_categoria == id)
        {
            rta=i;
        }
        i++;
    }
    return rta;
}

int agregarCatComida(CatComida arreglo[], categoria nvaCat, int validos)
{
    arreglo[validos].dato.id_categoria = nvaCat.id_categoria;
    strcpy(arreglo[validos].dato.nombre_cat, nvaCat.nombre_cat);
    arreglo[validos].lista=inicLista();
    validos++;

    return validos;
}

comida agregarComida(stDatosComida dtosComida)
{
    comida nvaComida;
    nvaComida.id = dtosComida.id;
    strcpy(nvaComida.nombre, dtosComida.nombre);
    nvaComida.precio = dtosComida.precio;

    return nvaComida;
}

categoria crearCatComida(stDatosComida dtosComida)
{

    categoria nvaCategoria;
    nvaCategoria.id_categoria = dtosComida.id_categoria;
    strcpy(nvaCategoria.nombre_cat, dtosComida.nombre_cat);
    return nvaCategoria;
}

int altaComidas(CatComida arreglo[], stDatosComida dtosComida, int validos)
{
    comida nvaComida = agregarComida(dtosComida);
    nodoComida *nvoNodo = crearNodo(nvaComida);
    int pos = buscarPosCatComida(arreglo, dtosComida.id_categoria, validos);
    if(pos == -1)
    {
        categoria nvaCategoria = crearCatComida(dtosComida);
        validos = agregarCatComida(arreglo, nvaCategoria, validos);
        pos = validos-1;
    }
    arreglo[pos].lista = agregarOrdenado(arreglo[pos].lista, nvoNodo);

    return validos;
}

void mostrarCategorias(CatComida arreglo[],  int validos)
{
    printf("\tCATEGORIAS\n");
    for(int i=0; i<validos; i++)
    {
        printf("%i - %s\n", arreglo[i].dato.id_categoria, arreglo[i].dato.nombre_cat);
    }
    printf("\n\n");
}

void mostrarArregloComidas(CatComida arreglo[], int validos)
{
    int i=0;
    while(i < validos)
    {
        printf("\tCATEGORIA: %s           ID:  %i\n\n", arreglo[i].dato.nombre_cat, arreglo[i].dato.id_categoria);
        mostrarListaComida(arreglo[i].lista);
        printf("--------------------------------------------------------------\n");
        printf("--------------------------------------------------------------\n");
        i++;
    }
}

void mostrarListaComida(nodoComida*lista)
{
    while(lista != NULL)
    {
        mostrarComida(lista->dato);
        lista = lista->siguiente;
    }
}

void mostrarComida(comida aux)
{
    printf("NOMBRE: %s\n",aux.nombre);
    printf("ID %d\n",aux.id);
    printf("PRECIO %.2f\n",aux.precio);
    printf("\n");
    printf("\n");
}

stDatosComida CargarUnaComida(CatComida arreglo[], int posCategoria)
{
    stDatosComida auxiliar;
    printf("Ingrese el nombre de la comida: \n");
    fflush(stdin);
    gets(auxiliar.nombre);
    int flag = validarNombreComida(arreglo[posCategoria].lista, auxiliar.nombre);
    if(flag == -1)
    {
        printf("No pueden haber dos comidas con el mismo nombre\n");
        printf("Ingrese el nombre de la comida: \n");
        fflush(stdin);
        gets(auxiliar.nombre);
    }

    printf("Ingrese la id de la comida: \n");
    scanf("%i", &auxiliar.id);
    int posCom = retornarIDcomida(arreglo[posCategoria].lista, auxiliar.id);
    while(posCom != -1)
    {
        printf("ID de comida no disponible, intente con un nuevo id: ");
        scanf("%i", &auxiliar.id);
        posCom= retornarIDcomida(arreglo[posCategoria].lista, auxiliar.id);
    }
    printf("Ingrese el precio de la comida: \n");
    fflush(stdin);
    scanf("%f", &auxiliar.precio);
    return auxiliar;
}


int ingresarNvaComida(CatComida arreglo[], int validos)
{
    stDatosComida auxiliar;
    char continuar = 's';
    while(continuar == 's')
    {
        printf("\t\t CARGA DE NUEVA COMIDA\n\n");
        mostrarCategorias(arreglo, validos);
        printf("Ingrese la id de la categoria: \n");
        fflush(stdin);
        scanf("%i", &auxiliar.id_categoria);
        int pos = buscarPosCatComida(arreglo,auxiliar.id_categoria, validos);
        while(pos == -1)
        {
            printf("Categoria invalida\n");
            printf("Ingrese una id existente : ");
            fflush(stdin);
            scanf("%i", &auxiliar.id_categoria);
            pos = buscarPosCatComida(arreglo, auxiliar.id_categoria, validos);
        }

        auxiliar = CargarUnaComida(arreglo, pos);
        auxiliar.id_categoria = arreglo[pos].dato.id_categoria;

        validos = altaComidas (arreglo, auxiliar, validos);
        cargarArchivo(auxiliar);

        printf("Desea continuar? presione s\n");
        fflush(stdin);
        scanf("%c", &continuar);
        system("CLS");
    }

    return validos;
}

int ingresarNvaCategria(CatComida arreglo[], int validos, int dimension)
{
    stDatosComida auxiliar;
    char continuar = 's';
    char nombre[20];
    while(continuar == 's')
    {
        if(validos < dimension)
        {
            printf("\t\t CARGA DE NUEVA CATEGORIA\n\n");
            mostrarCategorias(arreglo, validos);
            printf("Ingrese el nombre de la categoria: \n");
            fflush(stdin);
            gets(nombre);
            int flag = validarNombreCat(arreglo, validos, nombre);
            if(flag == -1)
            {
                printf("No pueden haber dos categorias con el mismo nombre\n");
                printf("Ingrese el nombre de la categoria: \n");
                fflush(stdin);
                gets(nombre);
            }

            auxiliar = CargarUnaComida(arreglo, validos);
            strcpy(auxiliar.nombre_cat, nombre);
            auxiliar.id_categoria = arreglo[validos-1].dato.id_categoria +1;

            validos = altaComidas (arreglo, auxiliar, validos);
            cargarArchivo(auxiliar);

            printf("Desea continuar? presione s\n");
            fflush(stdin);
            scanf("%c", &continuar);
            system("CLS");

        }

        else
        {
            printf("NO SE PUEDE CREAR OTRA CATEGORIA\n");
            printf("Vuelva al menu e ingrese nueva comida en categoria existente\n");
            continuar = 'n';
        }

    }

    return validos;
}


int validarNombreCat(CatComida arreglo[], int validos, char nombre[])
{
    int aux = 0;
    int i=0;
    while( i < validos && aux == 0)
    {
        if(strcmpi(arreglo[i].dato.nombre_cat, nombre) == 0)
        {
            aux =-1;
        }
        i++;
    }
    return aux;
}

int validarCat(CatComida arreglo[], int validos, int auxiliar)
{
    int aux = -1;
    int pos = buscarPosCatComida(arreglo, auxiliar, validos);
    if(pos != -1)
    {
        aux = pos;
    }
    return aux;
}

int validarNombreComida(nodoComida *lista, char nombre[])
{
    int aux = 0;
    while( lista != NULL && aux == 0)
    {
        if(strcmpi(lista->dato.nombre, nombre) == 0)
        {
            aux =-1;
        }
        lista = lista->siguiente;
    }
    return aux;
}

int seleccionarCategoria(CatComida arreglo[], int validos)
{
    int cat;
    printf("Ingrese id de la categoria: ");
    scanf("%i", &cat);

    return cat;
}

int seleccionarComida(nodoComida *lista)
{
    int auxiliar;
    printf("ID de la comida: ");
    scanf("%i", &auxiliar);

    return auxiliar;
}

void BorrarUnaComida(CatComida arreglo[], int validos)
{
    printf("\tBORRAR COMIDA\n\n");
    mostrarCategorias(arreglo, validos);
    int cat = seleccionarCategoria(arreglo, validos);
    int pos = buscarPosCatComida(arreglo, cat, validos);
    while (pos == -1)
    {
        printf("Categoria incorrecta\n");
        cat = seleccionarCategoria(arreglo, validos);
        pos = buscarPosCatComida(arreglo, cat, validos);
    }
    system("CLS");
    mostrarListaComida(arreglo[pos].lista);
    int auxiliar = seleccionarComida(arreglo[pos].lista);
    nodoComida *comidaBorrar = encontrarComida(arreglo[pos].lista, auxiliar);
    while(comidaBorrar == NULL)
    {
        printf("No hay comidas con esa id\n ");
        auxiliar = seleccionarComida(arreglo[pos].lista);
        comidaBorrar = encontrarComida(arreglo[pos].lista, auxiliar);
    }

    arreglo[pos].lista = borrarNodo(arreglo[pos].lista, auxiliar);

}



nodoComida *borrarNodo(nodoComida *lista, int id)
{
    if (lista != NULL)
    {
        if(lista->dato.id == id)
        {
            nodoComida *aBorrar = lista;
            lista = lista->siguiente;
            if(lista != NULL)
            {
                lista->anterior = NULL;
            }
            free(aBorrar);
        }
        else
        {
            nodoComida *seguidora = lista;
            while(seguidora != NULL && seguidora->dato.id != id)
            {
                seguidora=seguidora->siguiente;
            }
            if(seguidora!= NULL)
            {
                nodoComida *anterior = seguidora->anterior;
                anterior->siguiente = seguidora->siguiente;
                if(seguidora->siguiente != NULL)
                {
                    nodoComida *seg = seguidora->siguiente;
                    seg =  anterior;
                }
                free(seguidora);
            }
        }
    }
    return lista;
}

void cambiarPrecioComida(CatComida arreglo[], int validos)
{
    printf("\tCAMBIOS DE PRECIOS\n");
    mostrarCategorias(arreglo, validos);
    int cat = seleccionarCategoria(arreglo, validos);
    int pos = buscarPosCatComida(arreglo, cat, validos);
    while (pos == -1)
    {
        printf("Categoria incorrecta, Ingrese un id valido\n ");
        cat = seleccionarCategoria(arreglo, validos);
        pos = buscarPosCatComida(arreglo, cat, validos);

    }
    system("CLS");
    mostrarListaComida(arreglo[pos].lista);
    int auxiliar = seleccionarComida(arreglo[pos].lista);
    nodoComida *comidaBuscada = encontrarComida(arreglo[pos].lista, auxiliar);
    while(comidaBuscada == NULL)
    {
        printf("No hay comidas con esa id");
        auxiliar = seleccionarComida(arreglo[pos].lista);
        comidaBuscada = encontrarComida(arreglo[pos].lista, auxiliar);
    }

    comidaBuscada = modificarNodo(comidaBuscada);

}


nodoComida *modificarNodo(nodoComida *nodoAux)
{
    printf("Ingrese el nuevo precio para %s: ", nodoAux->dato.nombre);
    scanf("%f", &nodoAux->dato.precio);

    return nodoAux;
}

int retornarIDcomida(nodoComida *lista, int id)
{
    int auxiliar =-1;
    while(lista != NULL && auxiliar == -1)
    {
        if(lista->dato.id == id)
        {
            auxiliar= lista->dato.id;
        }
        lista=lista->siguiente;
    }
    return auxiliar;
}

nodoComida *encontrarComida(nodoComida *lista, int id)
{
    nodoComida *ComidaBuscada = NULL;
    int flag=0;
    while(lista != NULL && flag == 0)
    {
        if(lista->dato.id == id)
        {
            ComidaBuscada=lista;
            flag=1;
        }
        lista=lista->siguiente;
    }
    return ComidaBuscada;
}

void cambiarPrecioUnaCategoria(CatComida arreglo[], int validos)
{
    int cat;
    float valor;
    printf("\tMODIFICAR PRECIO DE UNA CATEGORIA\n");
    mostrarCategorias(arreglo, validos);
    printf("Ingrese el id de la categoria: ");
    scanf("%i", &cat);
    int pos = buscarPosCatComida(arreglo, cat, validos);
    while(pos == -1)
    {
        printf("Categoria invalida, vuelva a ingresar el id categoria: ");
        scanf("%i", &cat);
        pos = buscarPosCatComida(arreglo, cat, validos);
    }
    system("PAUSE");
    system("CLS");
    mostrarListaComida(arreglo[pos].lista);
    printf("Que porcentaje desea aumentar?: ");
    scanf("%f", &valor);
    arreglo[pos].lista = ModificarPrecioLista(arreglo[pos].lista, valor);
    system("PAUSE");
    system("CLS");
    mostrarListaComida(arreglo[pos].lista);
}


nodoComida *ModificarPrecioLista(nodoComida *lista, float valor)
{
    float total;
    nodoComida *aux = lista;
    if (lista != NULL)
    {
        while(lista != NULL)
        {
            total = (float)lista->dato.precio * (float)valor;
            lista->dato.precio = total;
            lista=lista->siguiente;
        }
    }
    return aux;
}


void persistirArchivoComidas(CatComida arreglo[], int validos)
{
    stDatosComida auxiliar;
    FILE *buffer = fopen("ArchivoComidas.bin", "wb");
    if(buffer)
    {
        for(int i=0; i<validos; i++)
        {
            while(arreglo[i].lista != NULL)
            {
                auxiliar=cargarComida(arreglo[i].dato, arreglo[i].lista);
                fwrite(&auxiliar,sizeof(stDatosComida), 1, buffer);
                arreglo[i].lista= arreglo[i].lista->siguiente;
            }
        }
        fclose(buffer);
    }

}

stDatosComida cargarComida(categoria dato, nodoComida *lista)
{
    stDatosComida aux;
    aux.id_categoria = dato.id_categoria;
    strcpy(aux.nombre_cat, dato.nombre_cat);
    strcpy(aux.nombre, lista->dato.nombre);
    aux.id = lista->dato.id;
    aux.precio = lista->dato.precio;

    return aux;

}

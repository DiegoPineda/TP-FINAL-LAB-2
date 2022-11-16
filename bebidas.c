#include "bebidas.h"

int menuBebida(CeldaBebida arreglo[], int validos)
{
    int elecc;
    do
    {


        printf("1.Mostrar Categorias y Bebidas\n2.Ingresar Nueva Bebida\n3.Ingresar Nueva Categoria\n4.Cambiar Precio Bebida\n5. Borrar una Bebida\n6. Cambiar Precio Una Categoria.\n0.Salir\n");
        fflush(stdin);
        scanf("%i",&elecc);
        switch(elecc)
        {
        case 1:
        {
            mostrarArregloBebidas(arreglo,validos);
            break;
        }
        case 2:
        {
            validos = ingresarNvaBebida(arreglo,validos);
            break;
        }
        case 3:
        {
            validos = ingresarNvaCategriaBebida(arreglo, validos, 50);
            break;
        }
        case 4:
        {
            cambiarPrecioBebida(arreglo, validos);
            break;
        }
        case 5:
        {
            BorrarUnaBebida(arreglo, validos);
            break;
        }
        case 6:
        {
            cambiarPrecioUnaCatBebida(arreglo, validos);
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

void mostrarArchiBebida()
{
    stDatosBebidas aux;
    FILE*archi=fopen("ArchivoBebida.bin","rb");
    if(archi!=NULL)
    {

        while(fread(&aux,sizeof(stDatosBebidas),1,archi)>0)
        {
            mostrarArchivoBebida(aux);

        }
        fclose(archi);
    }
}

void mostrarArchivoBebida(stDatosBebidas aux)
{
    printf("ID %d\n",aux.id);
    printf("NOMBRE %s\n",aux.nombre);
    printf("PRECIO %.2f\n",aux.precio);
    printf("CANTIDAD %s\n",aux.cantidad);
    printf("id categoria %i\n",aux.id_categoria);
    printf("Nombre categoria %s\n",aux.nombre_cat);
    printf("--------------------------------------------------------------------------------------------\n");
    printf("\n");
}

void cargarArchivoBebida1()
{
    stDatosBebidas auxiliar;
    FILE *buffer = fopen("ArchivoBebida.bin", "ab");
    if(buffer != NULL)
    {
        char continuar = 's';
        while(continuar == 's')
        {
            auxiliar = cargarStructBebida();
            fwrite(&auxiliar, sizeof(stDatosBebidas), 1, buffer);
            printf("Desea continuar? presione s\n");
            fflush(stdin);
            scanf("%c", &continuar);
            system("CLS");
        }

        fclose(buffer);
    }
}

void cargarArchivoBebida(stDatosBebidas auxiliar)
{

    FILE *buffer = fopen("ArchivoBebida.bin", "ab");
    if(buffer != NULL)
    {
        fwrite(&auxiliar, sizeof(stDatosBebidas), 1, buffer);

        fclose(buffer);
    }
}

stDatosBebidas cargarStructBebida()
{
    printf("\t\t CARGA DE UNA NUEVA BEBIDA\n");
    stDatosBebidas auxiliar;
    printf("Ingrese el nombre de la categoria: \n");
    fflush(stdin);
    gets(auxiliar.nombre_cat);
    printf("Ingrese la id de la categoria: \n");
    fflush(stdin);
    scanf("%i", &auxiliar.id_categoria);
    printf("Ingrese el nombre de la bebida: \n");
    fflush(stdin);
    gets(auxiliar.nombre);
    printf("Ingrese la id del postre: \n");
    fflush(stdin);
    scanf("%i", &auxiliar.id);
    printf("Ingrese el contenido de la bebida: \n");
    fflush(stdin);
    gets(auxiliar.cantidad);
    printf("Ingrese el precio: \n");
    fflush(stdin);
    scanf("%f", &auxiliar.precio);

    return auxiliar;

}

nodoBebida *inicListaBebida()
{
    return NULL;
}

nodoBebida *crearNodoBebida(bebida dato)
{
    nodoBebida *aux=(nodoBebida*) malloc(sizeof(nodoBebida));
    aux->dato = dato;
    aux->anterior = NULL;
    aux->siguiente = NULL;
    return aux;
}

nodoBebida *agregarAlPrincipioBebida(nodoBebida *lista, nodoBebida *nvoNodo)
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

nodoBebida *agregarOrdenadoBebida(nodoBebida *lista, nodoBebida *nvoNodo)
{
    if(lista == NULL)
    {
        lista = nvoNodo;
    }
    else
    {
        if(nvoNodo->dato.id < lista->dato.id)
        {
            lista = agregarAlPrincipioBebida(lista, nvoNodo);
        }
        else
        {
            nodoBebida *anterior = lista;
            nodoBebida *seguidora = lista->siguiente;
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

int leerArvchivoBebida(CeldaBebida arreglo[], int dimension)
{
    int validos =0;
    FILE *buffer = fopen("ArchivoBebida.bin", "rb");
    stDatosBebidas datosBebida;
    if(buffer != NULL)
    {
        while(fread(&datosBebida, sizeof(stDatosBebidas), 1, buffer) > 0 && validos < dimension)
        {
            validos = altaBebidas(arreglo, datosBebida, validos);
        }
        fclose(buffer);
    }

    return validos;
}

int buscarPosCatBebida(CeldaBebida arreglo[], int id, int validos)
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

int agregarCatBebida(CeldaBebida arreglo[], categoriaBebida nvaCat, int validos)
{
    arreglo[validos].dato.id_categoria = nvaCat.id_categoria;
    strcpy(arreglo[validos].dato.nombre_cat, nvaCat.nombre_cat);
    arreglo[validos].lista=inicListaBebida();
    validos++;

    return validos;
}

bebida agregarBebida(stDatosBebidas dtosBebida)
{
    bebida nvaBebida;
    nvaBebida.id = dtosBebida.id;
    strcpy(nvaBebida.nombre, dtosBebida.nombre);
    nvaBebida.precio = dtosBebida.precio;
    strcpy(nvaBebida.cantidad, dtosBebida.cantidad);

    return nvaBebida;
}

categoriaBebida crearCatBebida(stDatosBebidas dtosBebida)
{

    categoriaBebida nvaCategoria;
    nvaCategoria.id_categoria = dtosBebida.id_categoria;
    strcpy(nvaCategoria.nombre_cat, dtosBebida.nombre_cat);
    return nvaCategoria;
}

int altaBebidas(CeldaBebida arreglo[], stDatosBebidas dtosBebida, int validos)
{
    bebida nvaBebida = agregarBebida(dtosBebida);
    nodoBebida *nvoNodo = crearNodoBebida(nvaBebida);
    int pos = buscarPosCatBebida(arreglo, dtosBebida.id_categoria, validos);
    if(pos == -1)
    {
        categoriaBebida nvaCategoria = crearCatBebida(dtosBebida);
        validos = agregarCatBebida(arreglo, nvaCategoria, validos);
        pos = validos-1;
    }
    arreglo[pos].lista = agregarOrdenadoBebida(arreglo[pos].lista, nvoNodo);

    return validos;
}

void mostrarCategoriasBebidas(CeldaBebida arreglo[],  int validos)
{
    printf("\tCATEGORIAS\n");
    for(int i=0; i<validos; i++)
    {
        printf("%i - %s\n", arreglo[i].dato.id_categoria, arreglo[i].dato.nombre_cat);
    }
    printf("\n\n");
}

void mostrarArregloBebidas(CeldaBebida arreglo[], int validos)
{
    int i=0;
    while(i < validos)
    {
        printf("\tCATEGORIA: %s           ID:  %i\n\n", arreglo[i].dato.nombre_cat, arreglo[i].dato.id_categoria);
        mostrarListaBebida(arreglo[i].lista);
        printf("--------------------------------------------------------------\n");
        printf("--------------------------------------------------------------\n");
        i++;
    }
}

void mostrarListaBebida(nodoBebida*lista)
{
    while(lista != NULL)
    {
        mostrarBebida(lista->dato);
        lista = lista->siguiente;
    }
}

void mostrarBebida(bebida aux)
{
    printf("NOMBRE: %s\n",aux.nombre);
    printf("ID: %d\n",aux.id);
    printf("CONTENIDO: %s\n",aux.cantidad);
    printf("PRECIO %.2f\n",aux.precio);
    printf("\n");
    printf("\n");
}

stDatosBebidas CargarUnaBebida(CeldaBebida arreglo[], int posCategoria)
{
    stDatosBebidas auxiliar;
    printf("Ingrese el nombre de la bebida: \n");
    fflush(stdin);
    gets(auxiliar.nombre);
    int flag = validarNombreBebida(arreglo[posCategoria].lista, auxiliar.nombre);
    if(flag == -1)
    {
        printf("No pueden haber dos Bebidas con el mismo nombre\n");
        printf("Ingrese el nombre de la Bebida: \n");
        fflush(stdin);
        gets(auxiliar.nombre);
    }

    printf("Ingrese la id de la Bebida: \n");
    scanf("%i", &auxiliar.id);
    int posCom = retornarIDbebida(arreglo[posCategoria].lista, auxiliar.id);
    while(posCom != -1)
    {
        printf("ID de la bebida no disponible, intente con un nuevo id: ");
        scanf("%i", &auxiliar.id);
        posCom= retornarIDbebida(arreglo[posCategoria].lista, auxiliar.id);
    }
    printf("Ingrese el contenido de la Bebida: \n");
    fflush(stdin);
    gets(auxiliar.cantidad);
    printf("Ingrese el precio de la Bebida: \n");
    fflush(stdin);
    scanf("%f", &auxiliar.precio);
    return auxiliar;
}

int ingresarNvaBebida(CeldaBebida arreglo[], int validos)
{
    stDatosBebidas auxiliar;
    char continuar = 's';
    while(continuar == 's')
    {
        printf("\t\t CARGA DE NUEVA BEBIDA\n\n");
        mostrarCategoriasBebidas(arreglo, validos);
        printf("Ingrese id de la bebida \n");
        fflush(stdin);
        scanf("%i", &auxiliar.id_categoria);
        int pos = buscarPosCatBebida(arreglo,auxiliar.id_categoria, validos);
        while(pos == -1)
        {
            printf("Categoria invalida\n");
            printf("Ingrese una id existente : ");
            fflush(stdin);
            scanf("%i", &auxiliar.id_categoria);
            pos = buscarPosCatBebida(arreglo, auxiliar.id_categoria, validos);
        }

        auxiliar = CargarUnaBebida(arreglo, pos);
        auxiliar.id_categoria = arreglo[pos].dato.id_categoria;

        validos = altaBebidas (arreglo, auxiliar, validos);
        cargarArchivoBebida(auxiliar);

        printf("Desea continuar? presione s\n");
        fflush(stdin);
        scanf("%c", &continuar);
        system("CLS");
    }

    return validos;
}

int ingresarNvaCategriaBebida(CeldaBebida arreglo[], int validos, int dimension)
{
    stDatosBebidas auxiliar;
    char continuar = 's';
    char nombre[20];
    if(validos < dimension)
    {
        printf("\t\t CARGA DE NUEVA CATEGORIA\n\n");
        mostrarCategoriasBebidas(arreglo, validos);
        printf("Ingrese el nombre de la categoria: \n");
        fflush(stdin);
        gets(nombre);
        int flag = validarNombreBebida(arreglo, nombre);
        while(flag == -1)
        {
            printf("No pueden haber dos categorias con el mismo nombre\n");
            printf("Ingrese el nombre de la categoria: \n");
            fflush(stdin);
            gets(nombre);
            flag = validarNombreBebida(arreglo, nombre);
        }

        strcpy(auxiliar.nombre_cat, nombre);
        printf("Ingrese la id de la categoria: ");
        scanf("%i", &auxiliar.id_categoria);
        int pos = buscarPosCatBebida(arreglo, auxiliar.id_categoria, validos);
        while(pos != -1)
        {
            printf("id en uso, ingrese una nueva: ");
            scanf("%i", &auxiliar.id_categoria);
            pos = buscarPosCatBebida(arreglo, auxiliar.id_categoria, validos);
        }
        printf("Ingrese el nombre de la comida: \n");
        fflush(stdin);
        gets(auxiliar.nombre);
        printf("Ingrese la id de la comida: \n");
        scanf("%i", &auxiliar.id);
        printf("Ingrese el contenido: ");
        fflush(stdin);
        gets(auxiliar.cantidad);
        printf("Ingrese el precio de la comida: \n");
        fflush(stdin);
        scanf("%f", &auxiliar.precio);
    }

    else
    {
        printf("NO SE PUEDE CREAR OTRA CATEGORIA\n");
        printf("Vuelva al menu e ingrese nueva comida en categoria existente\n");
        continuar = 'n';
    }
        validos=altaBebidas(arreglo,auxiliar,validos);
        mostrarCategoriasBebidas(arreglo, validos);

    return validos;
}

int validarNombreCatBebida(CeldaBebida arreglo[], int validos, char nombre[])
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

int validarCatBebida(CeldaBebida arreglo[], int validos, int auxiliar)
{
    int aux = -1;
    int pos = buscarPosCatBebida(arreglo, auxiliar, validos);
    if(pos != -1)
    {
        aux = pos;
    }
    return aux;
}

int validarNombreBebida(nodoBebida *lista, char nombre[])
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

int seleccionarCategoriaBebida(CeldaBebida arreglo[], int validos)
{
    int cat;
    printf("Ingrese id de la categoria: ");
    scanf("%i", &cat);

    return cat;
}

int seleccionarBebida(nodoBebida *lista)
{
    int auxiliar;
    printf("ID de la Bebida: ");
    scanf("%i", &auxiliar);

    return auxiliar;
}

void BorrarUnaBebida(CeldaBebida arreglo[], int validos)
{
    printf("\tBorrar una Bebida\n\n");
    mostrarCategoriasBebidas(arreglo, validos);
    int cat = seleccionarCategoriaBebida(arreglo, validos);
    int pos = buscarPosCatBebida(arreglo, cat, validos);
    while (pos == -1)
    {
        printf("Categoria incorrecta\n");
        cat = seleccionarCategoriaBebida(arreglo, validos);
        pos = buscarPosCatBebida(arreglo, cat, validos);
    }
    system("CLS");
    mostrarListaBebida(arreglo[pos].lista);
    int auxiliar = seleccionarBebida(arreglo[pos].lista);
    nodoBebida *bebidaBorrar = encontrarBebida(arreglo[pos].lista, auxiliar);
    while(bebidaBorrar == NULL)
    {
        printf("No hay postres con esa id\n ");
        auxiliar = seleccionarBebida(arreglo[pos].lista);
        bebidaBorrar = encontrarBebida(arreglo[pos].lista, auxiliar);
    }

    arreglo[pos].lista = borrarNodoBebida(arreglo[pos].lista, auxiliar);

}

nodoBebida *borrarNodoBebida(nodoBebida *lista, int id)
{
    if (lista != NULL)
    {
        if(lista->dato.id == id)
        {
            nodoBebida *aBorrar = lista;
            lista = lista->siguiente;
            if(lista != NULL)
            {
                lista->anterior = NULL;
            }
            free(aBorrar);
        }
        else
        {
            nodoBebida *seguidora = lista;
            while(seguidora != NULL && seguidora->dato.id != id)
            {
                seguidora=seguidora->siguiente;
            }
            if(seguidora!= NULL)
            {
                nodoBebida *anterior = seguidora->anterior;
                anterior->siguiente = seguidora->siguiente;
                if(seguidora->siguiente != NULL)
                {
                    nodoBebida *seg = seguidora->siguiente;
                    seg =  anterior;
                }
                free(seguidora);
            }
        }
    }
    return lista;
}

void cambiarPrecioBebida(CeldaBebida arreglo[], int validos)
{
    printf("\tCAMBIAR PRECIO A UN PRODUCTO\n");
    mostrarCategoriasBebidas(arreglo, validos);
    int cat = seleccionarCategoriaBebida(arreglo, validos);
    int pos = buscarPosCatBebida(arreglo, cat, validos);
    while (pos == -1)
    {
        printf("Categoria incorrecta, Ingrese un id valido\n ");
        cat = seleccionarCategoriaBebida(arreglo, validos);
        pos = buscarPosCatBebida(arreglo, cat, validos);

    }
    system("CLS");
    mostrarListaBebida(arreglo[pos].lista);
    int auxiliar = seleccionarBebida(arreglo[pos].lista);
    nodoBebida *bebidaBuscada = encontrarBebida(arreglo[pos].lista, auxiliar);
    while(bebidaBuscada == NULL)
    {
        printf("No hay bebidad con ese id");
        auxiliar = seleccionarBebida(arreglo[pos].lista);
        bebidaBuscada= encontrarBebida(arreglo[pos].lista, auxiliar);
    }

    bebidaBuscada = modificarNodoBebida(bebidaBuscada);

}

nodoBebida *modificarNodoBebida(nodoBebida *nodoAux)
{
    printf("Ingrese el nuevo precio para %s: ", nodoAux->dato.nombre);
    scanf("%f", &nodoAux->dato.precio);

    return nodoAux;
}

int retornarIDbebida(nodoBebida *lista, int id)
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

nodoBebida *encontrarBebida(nodoBebida *lista, int id)
{
    nodoBebida *bebidaBuscada = NULL;
    int flag=0;
    while(lista != NULL && flag == 0)
    {
        if(lista->dato.id == id)
        {
            bebidaBuscada=lista;
            flag=1;
        }
        lista=lista->siguiente;
    }
    return bebidaBuscada;
}

void cambiarPrecioUnaCatBebida(CeldaBebida arreglo[], int validos)
{
    int cat;
    float valor;
    printf("\tMODIFICAR PRECIO DE UNA CATEGORIA\n");
    mostrarCategoriasBebidas(arreglo, validos);
    printf("Ingrese el id de la categoria: ");
    scanf("%i", &cat);
    int pos = buscarPosCatBebida(arreglo, cat, validos);
    while(pos == -1)
    {
        printf("Categoria invalida, vuelva a ingresar el id categoria: ");
        scanf("%i", &cat);
        pos = buscarPosCatBebida(arreglo, cat, validos);
    }
    system("PAUSE");
    system("CLS");
    mostrarListaBebida(arreglo[pos].lista);
    printf("Que porcentaje desea aumentar?: ");
    scanf("%f", &valor);
    arreglo[pos].lista = ModificarPrecioListaBebida(arreglo[pos].lista, valor);
    system("PAUSE");
    system("CLS");
    mostrarListaBebida(arreglo[pos].lista);
}

nodoBebida *ModificarPrecioListaBebida(nodoBebida *lista, float valor)
{
    float total;
    nodoBebida *aux = lista;
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

void persistirArchivoBebida(CeldaBebida arreglo[], int validos)
{
    stDatosBebidas auxiliar;
    FILE *buffer = fopen("ArchivoBebida.bin", "wb");
    if(buffer)
    {
        for(int i=0; i<validos; i++)
        {
            while(arreglo[i].lista != NULL)
            {
                auxiliar=cargarBebida(arreglo[i].dato, arreglo[i].lista);
                fwrite(&auxiliar,sizeof(stDatosBebidas), 1, buffer);
                arreglo[i].lista= arreglo[i].lista->siguiente;
            }
        }
        fclose(buffer);
    }

}

stDatosBebidas cargarBebida(categoriaBebida dato, nodoBebida *lista)
{
    stDatosBebidas aux;
    aux.id_categoria = dato.id_categoria;
    strcpy(aux.nombre_cat, dato.nombre_cat);
    strcpy(aux.nombre, lista->dato.nombre);
    aux.id = lista->dato.id;
    strcpy(aux.cantidad, lista->dato.cantidad);
    aux.precio = lista->dato.precio;

    return aux;

}

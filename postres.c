#include "postres.h"
int menuPostre(CeldaPostre arreglo[], int validos)
{
    int elecc;
    do
    {


        printf("1.Mostrar Categorias y Postres\n2.Ingresar Nuevo Postre\n3.Ingresar Nueva Categoria\n4.Cambiar Precio Postre\n5. Borrar un Postre\n6. Cambiar Precio Una Categoria.\n0.Salir\n");
        fflush(stdin);
        scanf("%i",&elecc);
        switch(elecc)
        {
        case 1:
        {
            mostrarArregloPostres(arreglo,validos);
            break;
        }
        case 2:
        {
            validos = ingresarNvoPostre(arreglo,validos);
            break;
        }
        case 3:
        {
            validos = ingresarNvaCategriaPostre(arreglo, validos, 50);
            break;
        }
        case 4:
        {
            cambiarPrecioPostre(arreglo, validos);
            break;
        }
        case 5:
        {
            BorrarUnPostre(arreglo, validos);
            break;
        }
        case 6:
        {
            cambiarPrecioUnaCatPostre(arreglo, validos);
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

void mostrarArchivoPos()
{
    stDatosPostres aux;
    FILE*archi=fopen("ArchivoPostres.bin","rb");
    if(archi!=NULL)
    {

        while(fread(&aux,sizeof(stDatosPostres),1,archi)>0)
        {
            mostrarArchivoPostres(aux);

        }
        fclose(archi);
    }
}

void mostrarArchivoPostres(stDatosPostres aux)
{
    printf("ID %d\n",aux.id);
    printf("NOMBRE %s\n",aux.nombre);
    printf("PRECIO %.2f\n",aux.precio);
    printf("id categoria %i\n",aux.id_categoria);
    printf("Nombre categoria %s\n",aux.nombre_cat);
    printf("--------------------------------------------------------------------------------------------\n");
    printf("\n");
}

void cargarArchivo2()
{
    stDatosPostres auxiliar;
    FILE *buffer = fopen("ArchivoPostres.bin", "ab");
    if(buffer != NULL)
    {
        char continuar = 's';
        while(continuar == 's')
        {
            auxiliar = cargarStructPostre();
            fwrite(&auxiliar, sizeof(stDatosPostres), 1, buffer);
            printf("Desea continuar? presione s\n");
            fflush(stdin);
            scanf("%c", &continuar);
            system("CLS");
        }

        fclose(buffer);
    }
}

void cargarArchivoPostres(stDatosPostres auxiliar)
{

    FILE *buffer = fopen("ArchivoPostres.bin", "ab");
    if(buffer != NULL)
    {
        fwrite(&auxiliar, sizeof(stDatosPostres), 1, buffer);

        fclose(buffer);
    }
}

stDatosPostres cargarStructPostre()
{
    printf("\t\t CARGA DE UN NUEVO POSTRE\n");
    stDatosPostres auxiliar;
    printf("Ingrese el nombre de la categoria: \n");
    fflush(stdin);
    gets(auxiliar.nombre_cat);
    printf("Ingrese la id de la categoria: \n");
    fflush(stdin);
    scanf("%i", &auxiliar.id_categoria);
    printf("Ingrese el nombre del postre: \n");
    fflush(stdin);
    gets(auxiliar.nombre);
    printf("Ingrese la id del postre: \n");
    fflush(stdin);
    scanf("%i", &auxiliar.id);
    printf("Ingrese el precio del postre: \n");
    fflush(stdin);
    scanf("%f", &auxiliar.precio);

    return auxiliar;

}

nodoPostre *inicListaPostre()
{
    return NULL;
}

nodoPostre *crearNodoPostre(postre dato)
{
    nodoPostre *aux=(nodoPostre*) malloc(sizeof(nodoPostre));
    aux->dato = dato;
    aux->anterior = NULL;
    aux->siguiente = NULL;
    return aux;
}

nodoPostre *agregarAlPrincipioPostre(nodoPostre *lista, nodoPostre *nvoNodo)
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

nodoPostre *agregarOrdenadoPostre(nodoPostre *lista, nodoPostre *nvoNodo)
{
    if(lista == NULL)
    {
        lista = nvoNodo;
    }
    else
    {
        if(nvoNodo->dato.id < lista->dato.id)
        {
            lista = agregarAlPrincipioPostre(lista, nvoNodo);
        }
        else
        {
            nodoPostre *anterior = lista;
            nodoPostre *seguidora = lista->siguiente;
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

int leerArvchivoPostres(CeldaPostre arreglo[], int dimension)
{
    int validos =0;
    FILE *buffer = fopen("ArchivoPostres.bin", "rb");
    stDatosPostres datosPostre;
    if(buffer != NULL)
    {
        while(fread(&datosPostre, sizeof(stDatosPostres), 1, buffer) > 0 && validos < dimension)
        {
            validos = altaPostres(arreglo, datosPostre, validos);
        }
        fclose(buffer);
    }

    return validos;
}

int buscarPosCatPostre(CeldaPostre arreglo[], int id, int validos)
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

int agregarCatPostre(CeldaPostre arreglo[], categoriaPostre nvaCat, int validos)
{
    arreglo[validos].dato.id_categoria = nvaCat.id_categoria;
    strcpy(arreglo[validos].dato.nombre_cat, nvaCat.nombre_cat);
    arreglo[validos].lista=inicListaPostre();
    validos++;

    return validos;
}

postre agregarPostre(stDatosPostres dtosPostre)
{
    postre nvoPostre;
    nvoPostre.id = dtosPostre.id;
    strcpy(nvoPostre.nombre, dtosPostre.nombre);
    nvoPostre.precio = dtosPostre.precio;

    return nvoPostre;
}

categoriaPostre crearCatPostre(stDatosPostres dtosPostre)
{

    categoriaPostre nvaCategoria;
    nvaCategoria.id_categoria = dtosPostre.id_categoria;
    strcpy(nvaCategoria.nombre_cat, dtosPostre.nombre_cat);
    return nvaCategoria;
}

int altaPostres(CeldaPostre arreglo[], stDatosPostres dtosPostre, int validos)
{
    postre nvoPostre = agregarPostre(dtosPostre);
    nodoPostre *nvoNodo = crearNodoPostre(nvoPostre);
    int pos = buscarPosCatPostre(arreglo, dtosPostre.id_categoria, validos);
    if(pos == -1)
    {
        categoriaPostre nvaCategoria = crearCatPostre(dtosPostre);
        validos = agregarCatPostre(arreglo, nvaCategoria, validos);
        pos = validos-1;
    }
    arreglo[pos].lista = agregarOrdenadoPostre(arreglo[pos].lista, nvoNodo);

    return validos;
}

void mostrarCategoriasPostres(CeldaPostre arreglo[],  int validos)
{
    printf("\tCATEGORIAS\n");
    for(int i=0; i<validos; i++)
    {
        printf("%i - %s\n", arreglo[i].dato.id_categoria, arreglo[i].dato.nombre_cat);
    }
    printf("\n\n");
}

void mostrarArregloPostres(CeldaPostre arreglo[], int validos)
{
    int i=0;
    while(i < validos)
    {
        printf("\tCATEGORIA: %s           ID:  %i\n\n", arreglo[i].dato.nombre_cat, arreglo[i].dato.id_categoria);
        mostrarListaPostres(arreglo[i].lista);
        printf("--------------------------------------------------------------\n");
        printf("--------------------------------------------------------------\n");
        i++;
    }
}

void mostrarListaPostres(nodoPostre*lista)
{
    while(lista != NULL)
    {
        mostrarPostre(lista->dato);
        lista = lista->siguiente;
    }
}

void mostrarPostre(postre aux)
{
    printf("NOMBRE: %s\n",aux.nombre);
    printf("ID %d\n",aux.id);
    printf("PRECIO %.2f\n",aux.precio);
    printf("\n");
    printf("\n");
}

stDatosPostres CargarUnPostre(CeldaPostre arreglo[], int posCategoria)
{
    stDatosPostres auxiliar;
    printf("Ingrese el nombre del postre: \n");
    fflush(stdin);
    gets(auxiliar.nombre);
    int flag = validarNombrePostre(arreglo[posCategoria].lista, auxiliar.nombre);
    if(flag == -1)
    {
        printf("No pueden haber dos postres con el mismo nombre\n");
        printf("Ingrese el nombre del postre: \n");
        fflush(stdin);
        gets(auxiliar.nombre);
    }

    printf("Ingrese la id del postre: \n");
    scanf("%i", &auxiliar.id);
    int posCom = retornarIDpostre(arreglo[posCategoria].lista, auxiliar.id);
    while(posCom != -1)
    {
        printf("ID del postre no disponible, intente con un nuevo id: ");
        scanf("%i", &auxiliar.id);
        posCom= retornarIDpostre(arreglo[posCategoria].lista, auxiliar.id);
    }
    printf("Ingrese el precio del postre: \n");
    fflush(stdin);
    scanf("%f", &auxiliar.precio);
    return auxiliar;
}

int ingresarNvoPostre(CeldaPostre arreglo[], int validos)
{
    stDatosPostres auxiliar;
    char continuar = 's';
    while(continuar == 's')
    {
        printf("\t\t CARGA DE NUEVO POSTRE\n\n");
        mostrarCategoriasPostres(arreglo, validos);
        printf("Ingrese id del postre: \n");
        fflush(stdin);
        scanf("%i", &auxiliar.id_categoria);
        int pos = buscarPosCatPostre(arreglo,auxiliar.id_categoria, validos);
        while(pos == -1)
        {
            printf("Categoria invalida\n");
            printf("Ingrese una id existente : ");
            fflush(stdin);
            scanf("%i", &auxiliar.id_categoria);
            pos = buscarPosCatPostre(arreglo, auxiliar.id_categoria, validos);
        }

        auxiliar = CargarUnPostre(arreglo, pos);
        auxiliar.id_categoria = arreglo[pos].dato.id_categoria;

        validos = altaPostres (arreglo, auxiliar, validos);
        cargarArchivoPostres(auxiliar);

        printf("Desea continuar? presione s\n");
        fflush(stdin);
        scanf("%c", &continuar);
        system("CLS");
    }

    return validos;
}

int ingresarNvaCategriaPostre(CeldaPostre arreglo[], int validos, int dimension)
{
    stDatosPostres auxiliar;
    char continuar = 's';
    char nombre[20];
    while(continuar == 's')
    {
        if(validos < dimension)
        {
            printf("\t\t CARGA DE NUEVa CATEGORIA\n\n");
            mostrarCategoriasPostres(arreglo, validos);
            printf("Ingrese el nombre de la categoria: \n");
            fflush(stdin);
            gets(nombre);
            int flag = validarNombreCatPostre(arreglo, validos, nombre);
            if(flag == -1)
            {
                printf("No pueden haber dos categorias con el mismo nombre\n");
                printf("Ingrese el nombre de la categoria: \n");
                fflush(stdin);
                gets(nombre);
            }

            auxiliar = CargarUnPostre(arreglo, validos);
            strcpy(auxiliar.nombre_cat, nombre);
            auxiliar.id_categoria = arreglo[validos-1].dato.id_categoria +1;

            validos = altaPostres(arreglo, auxiliar, validos);
            cargarArchivoPostres(auxiliar);

            printf("Desea continuar? presione s\n");
            fflush(stdin);
            scanf("%c", &continuar);
            system("CLS");

        }

        else
        {
            printf("NO SE PUEDE CREAR OTRA CATEGORIA\n");
            printf("Vuelva al menu e ingrese el postre en una categoria existente\n");
            continuar = 'n';
        }

    }

    return validos;
}

int validarNombreCatPostre(CeldaPostre arreglo[], int validos, char nombre[])
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

int validarCatPostre(CeldaPostre arreglo[], int validos, int auxiliar)
{
    int aux = -1;
    int pos = buscarPosCatPostre(arreglo, auxiliar, validos);
    if(pos != -1)
    {
        aux = pos;
    }
    return aux;
}

int validarNombrePostre(nodoPostre *lista, char nombre[])
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

int seleccionarCategoriaPostre(CeldaPostre arreglo[], int validos)
{
    int cat;
    printf("Ingrese id de la categoria: ");
    scanf("%i", &cat);

    return cat;
}

int seleccionarPostre(nodoPostre *lista)
{
    int auxiliar;
    printf("ID del postre: ");
    scanf("%i", &auxiliar);

    return auxiliar;
}

void BorrarUnPostre(CeldaPostre arreglo[], int validos)
{
    printf("\tBORRAR UN POSTRE\n\n");
    mostrarCategoriasPostres(arreglo, validos);
    int cat = seleccionarCategoriaPostre(arreglo, validos);
    int pos = buscarPosCatPostre(arreglo, cat, validos);
    while (pos == -1)
    {
        printf("Categoria incorrecta\n");
        cat = seleccionarCategoriaPostre(arreglo, validos);
        pos = buscarPosCatPostre(arreglo, cat, validos);
    }
    system("CLS");
    mostrarListaPostres(arreglo[pos].lista);
    int auxiliar = seleccionarPostre(arreglo[pos].lista);
    nodoPostre *postreBorrar = encontrarPostre(arreglo[pos].lista, auxiliar);
    while(postreBorrar == NULL)
    {
        printf("No hay postres con esa id\n ");
        auxiliar = seleccionarPostre(arreglo[pos].lista);
        postreBorrar = encontrarPostre(arreglo[pos].lista, auxiliar);
    }

    arreglo[pos].lista = borrarNodoPostre(arreglo[pos].lista, auxiliar);

}

nodoPostre *borrarNodoPostre(nodoPostre *lista, int id)
{
    if (lista != NULL)
    {
        if(lista->dato.id == id)
        {
            nodoPostre *aBorrar = lista;
            lista = lista->siguiente;
            if(lista != NULL)
            {
                lista->anterior = NULL;
            }
            free(aBorrar);
        }
        else
        {
            nodoPostre *seguidora = lista;
            while(seguidora != NULL && seguidora->dato.id != id)
            {
                seguidora=seguidora->siguiente;
            }
            if(seguidora!= NULL)
            {
                nodoPostre *anterior = seguidora->anterior;
                anterior->siguiente = seguidora->siguiente;
                if(seguidora->siguiente != NULL)
                {
                    nodoPostre *seg = seguidora->siguiente;
                    seg =  anterior;
                }
                free(seguidora);
            }
        }
    }
    return lista;
}

void cambiarPrecioPostre(CeldaPostre arreglo[], int validos)
{
    printf("\tCAMBIOS DE PRECIOS\n");
    mostrarCategoriasPostres(arreglo, validos);
    int cat = seleccionarCategoriaPostre(arreglo, validos);
    int pos = buscarPosCatPostre(arreglo, cat, validos);
    while (pos == -1)
    {
        printf("Categoria incorrecta, Ingrese un id valido\n ");
        cat = seleccionarCategoriaPostre(arreglo, validos);
        pos = buscarPosCatPostre(arreglo, cat, validos);

    }
    system("CLS");
    mostrarListaPostres(arreglo[pos].lista);
    int auxiliar = seleccionarPostre(arreglo[pos].lista);
    nodoPostre *postreBuscado = encontrarPostre(arreglo[pos].lista, auxiliar);
    while(postreBuscado == NULL)
    {
        printf("No hay postres con ese id");
        auxiliar = seleccionarPostre(arreglo[pos].lista);
        postreBuscado= encontrarPostre(arreglo[pos].lista, auxiliar);
    }

    postreBuscado = modificarNodoPostre(postreBuscado);

}

nodoPostre *modificarNodoPostre(nodoPostre *nodoAux)
{
    printf("Ingrese el nuevo precio para %s: ", nodoAux->dato.nombre);
    scanf("%f", &nodoAux->dato.precio);

    return nodoAux;
}

int retornarIDpostre(nodoPostre *lista, int id)
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

nodoPostre *encontrarPostre(nodoPostre *lista, int id)
{
    nodoPostre *postreBuscado = NULL;
    int flag=0;
    while(lista != NULL && flag == 0)
    {
        if(lista->dato.id == id)
        {
            postreBuscado=lista;
            flag=1;
        }
        lista=lista->siguiente;
    }
    return postreBuscado;
}

void cambiarPrecioUnaCatPostre(CeldaPostre arreglo[], int validos)
{
    int cat;
    float valor;
    printf("\tMODIFICAR PRECIO DE UNA CATEGORIA\n");
    mostrarCategoriasPostres(arreglo, validos);
    printf("Ingrese el id de la categoria: ");
    scanf("%i", &cat);
    int pos = buscarPosCatPostre(arreglo, cat, validos);
    while(pos == -1)
    {
        printf("Categoria invalida, vuelva a ingresar el id categoria: ");
        scanf("%i", &cat);
        pos = buscarPosCatPostre(arreglo, cat, validos);
    }
    system("PAUSE");
    system("CLS");
    mostrarListaPostres(arreglo[pos].lista);
    printf("Que porcentaje desea aumentar?: ");
    scanf("%f", &valor);
    arreglo[pos].lista = ModificarPrecioListaPostre(arreglo[pos].lista, valor);
    system("PAUSE");
    system("CLS");
    mostrarListaPostres(arreglo[pos].lista);
}

nodoPostre *ModificarPrecioListaPostre(nodoPostre *lista, float valor)
{
    float total;
    nodoPostre *aux = lista;
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


void persistirArchivoPostres(CeldaPostre arreglo[], int validos)
{
    stDatosPostres auxiliar;
    FILE *buffer = fopen("ArchivoPostres.bin", "wb");
    if(buffer)
    {
        for(int i=0; i<validos; i++)
        {
            while(arreglo[i].lista != NULL)
            {
                auxiliar=cargarPostre(arreglo[i].dato, arreglo[i].lista);
                fwrite(&auxiliar,sizeof(stDatosPostres), 1, buffer);
                arreglo[i].lista= arreglo[i].lista->siguiente;
            }
        }
        fclose(buffer);
    }

}

stDatosPostres cargarPostre(categoriaPostre dato, nodoPostre *lista)
{
    stDatosPostres aux;
    aux.id_categoria = dato.id_categoria;
    strcpy(aux.nombre_cat, dato.nombre_cat);
    strcpy(aux.nombre, lista->dato.nombre);
    aux.id = lista->dato.id;
    aux.precio = lista->dato.precio;

    return aux;

}
